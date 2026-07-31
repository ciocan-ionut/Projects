package app.server;

import app.model.SwimmingTestDTO;
import app.services.IObserver;
import app.services.IService;
import networking.grpc.*;
import io.grpc.stub.StreamObserver;

import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class ProtoService extends ProtoServiceGrpc.ProtoServiceImplBase implements IObserver {
    private final IService serverLogic;

    private final Set<StreamObserver<UpdateNotification>> clientObservers = ConcurrentHashMap.newKeySet();

    public ProtoService(IService serverLogic) {
        this.serverLogic = serverLogic;
    }

    @Override
    public void login(LoginRequest request, StreamObserver<EmptyResponse> responseObserver) {
        try {
            serverLogic.login(request.getUsername(), request.getPassword(), this);

            responseObserver.onNext(EmptyResponse.newBuilder().build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void logout(LogoutRequest request, StreamObserver<EmptyResponse> responseObserver) {
        try {
            serverLogic.logout(request.getUsername(), this);
            responseObserver.onNext(EmptyResponse.newBuilder().build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void subscribeToUpdates(EmptyRequest request, StreamObserver<UpdateNotification> responseObserver) {
        clientObservers.add(responseObserver);
    }

    @Override
    public void update() {
        UpdateNotification notification = UpdateNotification.newBuilder()
                .setMessage("TableUpdated")
                .build();

        for (StreamObserver<UpdateNotification> observer : clientObservers) {
            try {
                synchronized (observer) {
                    observer.onNext(notification);
                }
            } catch (Exception e) {
                clientObservers.remove(observer);
            }
        }
    }

    @Override
    public void getAllSwimmingTests(EmptyRequest request, StreamObserver<SwimmingTestDTOList> responseObserver) {
        try {
            List<SwimmingTestDTO> testeDtb = serverLogic.getAllSwimmingTestDTOs();

            SwimmingTestDTOList.Builder listBuilder = SwimmingTestDTOList.newBuilder();
            for (app.model.SwimmingTestDTO t : testeDtb) {
                listBuilder.addTests(networking.grpc.SwimmingTestDTO.newBuilder()
                        .setId(t.id())
                        .setStyle(t.style())
                        .setDistance(t.distance())
                        .setParticipantCount((int) t.participantCount())
                        .build());
            }

            responseObserver.onNext(listBuilder.build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void getSwimmingTestsForParticipant(ParticipantIdRequest request, StreamObserver<SwimmingTestList> responseObserver) {
        try {
            List<app.model.SwimmingTest> testeParticipant = serverLogic.getSwimmingTestsForParticipant(request.getParticipantId());

            SwimmingTestList.Builder listBuilder = SwimmingTestList.newBuilder();
            for (app.model.SwimmingTest t : testeParticipant) {
                listBuilder.addTests(networking.grpc.SwimmingTest.newBuilder()
                        .setId(t.getId())
                        .setStyle(t.getStyle())
                        .setDistance(t.getDistance())
                        .build());
            }

            responseObserver.onNext(listBuilder.build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void getParticipants(SwimmingTestIdRequest request, StreamObserver<ParticipantDTOList> responseObserver) {
        try {
            List<app.model.ParticipantDTO> participanti = serverLogic.getAllParticipantDTOs(request.getSwimmingTestId());

            ParticipantDTOList.Builder listBuilder = ParticipantDTOList.newBuilder();
            for (app.model.ParticipantDTO p : participanti) {
                listBuilder.addParticipants(networking.grpc.ParticipantDTO.newBuilder()
                        .setId(p.id())
                        .setName(p.name())
                        .setAge(p.age())
                        .build());
            }

            responseObserver.onNext(listBuilder.build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void addParticipant(AddParticipantRequest request, StreamObserver<EmptyResponse> responseObserver) {
        try {
            List<app.model.SwimmingTest> modelTests = request.getTestsList().stream()
                    .map(t -> new app.model.SwimmingTest(t.getId(), t.getDistance(), t.getStyle()))
                    .collect(Collectors.toList());

            serverLogic.addParticipant(request.getName(), request.getAge(), modelTests);

            responseObserver.onNext(EmptyResponse.newBuilder().build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }

    @Override
    public void updateParticipant(UpdateParticipantRequest request, StreamObserver<EmptyResponse> responseObserver) {
        try {
            app.model.ParticipantDTO participantDTO = new app.model.ParticipantDTO(request.getParticipant().getId(), request.getParticipant().getName(), request.getParticipant().getAge(), 0);

            List<app.model.SwimmingTest> modelTests = request.getTestsList().stream()
                    .map(t -> new app.model.SwimmingTest(t.getId(), t.getDistance(), t.getStyle()))
                    .collect(Collectors.toList());

            serverLogic.updateParticipant(participantDTO, modelTests);

            responseObserver.onNext(EmptyResponse.newBuilder().build());
            responseObserver.onCompleted();
        } catch (Exception e) {
            responseObserver.onError(io.grpc.Status.INTERNAL.withDescription(e.getMessage()).asRuntimeException());
        }
    }
}

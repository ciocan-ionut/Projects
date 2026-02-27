package events;

import domain.duck.SwimmingDuck;
import utils.TipEvent;

import java.util.ArrayList;
import java.util.List;

public class RaceEvent extends Event {
    private final List<SwimmingDuck> ducks;
    private final List<Long> distances;
    private double bestTime;
    private List<Integer> bestAssignment;

    public RaceEvent(Long id, String name, TipEvent type, List<SwimmingDuck> ducks, List<Long> distances) {
        super(id, name, type);
        this.ducks = ducks;
        this.distances = distances;
    }

    public List<SwimmingDuck> getDucks() {
        return ducks;
    }

    public List<Long> getDistances() {
        return distances;
    }

    public void startRace(){
        bubbleSortDucks();
        binarySearch();
        showResults();
    }

    private void bubbleSortDucks() {
        for (int i = 0; i < ducks.size() - 1; i++) {
            boolean swapped = false;
            for(int j = 0; j < ducks.size() - i - 1; j++) {
                if(ducks.get(j).getResistance() > ducks.get(j+1).getResistance()) {
                    SwimmingDuck temp = ducks.get(j);
                    ducks.set(j, ducks.get(j + 1));
                    ducks.set(j + 1, temp);
                    swapped = true;
                }
            }
            if(!swapped) {
                break;
            }
        }
    }

    private void binarySearch() {
        double low = 0, high = 10, eps = 1e-3;
        double best = high;
        List<Integer> bestAssign = null;

        for (int i = 0; i < 60; i++) {
            double mid = (low + high) / 2;
            List<Integer> assign = feasible(mid);
            if (assign != null) {
                best = mid;
                bestAssign = assign;
                high = mid;
            } else {
                low = mid;
            }
            if (high - low <= eps)
                break;
        }

        bestTime = best;
        bestAssignment = bestAssign;
    }

    private List<Integer> feasible(double time) {
        int nrDucks = ducks.size();
        int nrLanes = distances.size();
        boolean[] usedDucks = new boolean[nrDucks];
        List<Integer> assign = new ArrayList<>(nrLanes);

        for (Long distance : distances) {
            int pick = -1;
            double requiredSpeed = (2.0 * distance) / time;
            for (int i = 0; i < nrDucks; i++) {
                if (ducks.get(i).getSpeed() >= requiredSpeed && !usedDucks[i]) {
                    pick = i;
                    break;
                }
            }

            if (pick == -1)
                return null;
            usedDucks[pick] = true;
            assign.add(pick);
        }
        return assign;
    }

    private void showResults(){
        if (bestAssignment == null)
            System.out.println("No results found");
        else {
            System.out.printf("Best time: %.3f%n", bestTime);
            for (int i = 0; i < distances.size(); i++) {
                SwimmingDuck duck = ducks.get(bestAssignment.get(i));
                double time = (distances.get(i) * 2.0) / duck.getSpeed();
                System.out.printf("Duck %d on lane %d: t=%.3f secunde%n", duck.getId(), i + 1, time);
            }
        }
    }
}

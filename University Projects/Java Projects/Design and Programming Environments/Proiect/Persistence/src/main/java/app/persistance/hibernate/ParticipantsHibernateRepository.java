package app.persistance.hibernate;

import app.model.Participant;
import app.model.ParticipantDTO;
import app.persistance.ParticipantRepository;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

public class ParticipantsHibernateRepository implements ParticipantRepository {
    private final SessionFactory sessionFactory;

    public ParticipantsHibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void save(Participant entity) {
        try (Session session = sessionFactory.openSession()) {
            Transaction tx = session.beginTransaction();
            session.merge(entity);
            tx.commit();
        }
    }

    @Override
    public void update(Participant entity) {
        try (Session session = sessionFactory.openSession()) {
            Transaction tx = session.beginTransaction();
            session.merge(entity);
            tx.commit();
        }
    }

    @Override
    public List<ParticipantDTO> findParticipantDTOsBySwimmingTestId(Integer swimmingTestId) {
        try (Session session = sessionFactory.openSession()) {
            String query = "select new app.model.ParticipantDTO(p.id, p.name, p.age, size(p.swimmingTests)) " +
                         "from Participant p join p.swimmingTests st " +
                         "where st.id = :testId";

            return session.createQuery(query, ParticipantDTO.class)
                    .setParameter("testId", swimmingTestId)
                    .list();
        }
    }

    @Override
    public void delete(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public Participant findById(Integer integer) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    @Override
    public List<Participant> findAll() {
        throw new UnsupportedOperationException("Not implemented yet");
    }
}

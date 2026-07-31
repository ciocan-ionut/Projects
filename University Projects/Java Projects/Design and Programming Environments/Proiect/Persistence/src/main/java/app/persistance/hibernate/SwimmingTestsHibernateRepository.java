package app.persistance.hibernate;

import app.model.SwimmingTest;
import app.model.SwimmingTestDTO;
import app.persistance.SwimmingTestRepository;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import java.util.List;

public class SwimmingTestsHibernateRepository implements SwimmingTestRepository {
    private final SessionFactory sessionFactory;

    public SwimmingTestsHibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public List<SwimmingTest> findSwimmingTestsByParticipantId(Integer participantId) {
        try (Session session = sessionFactory.openSession()) {
            String query = "select st from Participant p join p.swimmingTests st where p.id = :pId";

            return session.createQuery(query, SwimmingTest.class)
                    .setParameter("pId", participantId)
                    .list();
        }
    }

    @Override
    public List<SwimmingTestDTO> findAllDTOs() {
        try (Session session = sessionFactory.openSession()) {
            String query = "select new app.model.SwimmingTestDTO(st.id, st.distance, st.style, " +
                         "(select count(p) from Participant p join p.swimmingTests t where t.id = st.id)) " +
                         "from SwimmingTest st";

            return session.createQuery(query, SwimmingTestDTO.class).list();
        }
    }

    @Override
    public List<SwimmingTest> findAll() {
        try (Session session = sessionFactory.openSession()) {
            return session.createQuery("from SwimmingTest", SwimmingTest.class).list();
        }
    }

    @Override
    public SwimmingTest findById(Integer id) {
        try (Session session = sessionFactory.openSession()) {
            return session.find(SwimmingTest.class, id);
        }
    }

    @Override
    public void save(SwimmingTest entity) {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            entity.setId(null);
            session.persist(entity);
            session.getTransaction().commit();
        }
    }

    @Override
    public void update(SwimmingTest entity) {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            session.merge(entity);
            session.getTransaction().commit();
        }
    }

    @Override
    public void delete(Integer id) {
        try (Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            SwimmingTest test = session.find(SwimmingTest.class, id);
            if (test != null) {
                session.remove(test);
            }
            session.getTransaction().commit();
        }
    }

    @Override
    public List<SwimmingTest> findByStyle(String style) {
        try (Session session = sessionFactory.openSession()) {
            return session.createQuery("from SwimmingTest where style = :styleParam", SwimmingTest.class)
                    .setParameter("styleParam", style)
                    .list();
        }
    }
}

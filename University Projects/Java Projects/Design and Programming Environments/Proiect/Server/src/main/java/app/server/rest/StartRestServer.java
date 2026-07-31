package app.server.rest;

import app.persistance.OrganizerRepository;
import app.persistance.SwimmingTestRepository;
import app.persistance.hibernate.SwimmingTestsHibernateRepository;
import app.persistance.repository.DBUtils;
import app.persistance.repository.OrganizersDBRepository;
import io.jsonwebtoken.Jwts;
import jakarta.servlet.Filter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.io.IOException;
import java.util.Properties;

@SpringBootApplication
public class StartRestServer {
    public static void main(String[] args) {
        SpringApplication.run(StartRestServer.class, args);
    }

    @Bean
    public SwimmingTestRepository swimmingTestRepository() {
        SessionFactory sessionFactory = new Configuration().configure("hibernate.cfg.xml").buildSessionFactory();
        return new SwimmingTestsHibernateRepository(sessionFactory);
    }

    @Bean
    public OrganizerRepository organizerRepository() {
        Properties prop = new Properties();
        try {
            prop.load(StartRestServer.class.getResourceAsStream("/bd.config"));
            prop.list(System.out);
        } catch (IOException e) {
            return null;
        }

        DBUtils dbUtils = new DBUtils(prop);
        return new OrganizersDBRepository(dbUtils);
    }

    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                registry.addMapping("/**")
                        .allowedOrigins("http://localhost:5173")
                        .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS")
                        .allowedHeaders("*")
                        .allowCredentials(true);
            }
        };
    }

    @Bean
    public Filter jwtFilter() {
        return (request, response, chain) -> {
            HttpServletRequest req = (HttpServletRequest) request;
            HttpServletResponse res = (HttpServletResponse) response;

            if (req.getRequestURI().startsWith("/api/auth") ||
                req.getRequestURI().startsWith("/ws") ||
                req.getMethod().equals("GET") ||
                req.getMethod().equals("OPTIONS")) {
                chain.doFilter(request, response);
                return;
            }

            String header = req.getHeader("Authorization");
            if (header == null || !header.startsWith("Bearer ")) {
                res.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                return;
            }

            try {
                String token = header.substring(7);
                Jwts.parser()
                        .setSigningKey("cheia-mea-secreta-foarte-lunga-si-sigura-1234567890".getBytes())
                        .build()
                        .parseClaimsJws(token);
                chain.doFilter(request, response);
            } catch (Exception e) {
                res.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            }
        };
    }
}

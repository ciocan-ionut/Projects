package app.server.rest;

import app.persistance.OrganizerRepository;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Date;
import java.util.Map;

@RestController
@RequestMapping("/api/auth")
public class AuthController {
    private final OrganizerRepository repository;

    @Autowired
    public AuthController(OrganizerRepository repository) {
        this.repository = repository;
    }

    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody Map<String, String> credentials) {
        String username  = credentials.get("username");
        String password = credentials.get("password");

        if (repository.findByUsernameAndPassword(username, password) != null) {
            String token = Jwts.builder()
                    .setSubject(username)
                    .setExpiration(new Date(System.currentTimeMillis() + 3600000)) // 1 hour expiration
                    .signWith(SignatureAlgorithm.HS256, "cheia-mea-secreta-foarte-lunga-si-sigura-1234567890".getBytes())
                    .compact();

            return ResponseEntity.ok(token);
        }
        return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Invalid credentials");
    }
}

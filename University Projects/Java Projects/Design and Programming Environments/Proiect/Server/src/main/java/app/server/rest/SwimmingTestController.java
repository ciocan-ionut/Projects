package app.server.rest;

import app.model.SwimmingTest;
import app.persistance.SwimmingTestRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/probe")
public class SwimmingTestController {
    private final SwimmingTestRepository repository;

    @Autowired
    public SwimmingTestController(SwimmingTestRepository repository) {
        this.repository = repository;
    }

    @Autowired
    private SimpMessagingTemplate messagingTemplate;

    @GetMapping("/{id}")
    public ResponseEntity<SwimmingTest> getById(@PathVariable Integer id) {
        SwimmingTest test = repository.findById(id);
        if (test == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>(test, HttpStatus.OK);
    }

    @GetMapping
    public List<SwimmingTest> getAll(@RequestParam(required = false) String style) {
        if (style != null && !style.isEmpty()) {
            return repository.findByStyle(style);
        }
        return repository.findAll();
    }

    @PostMapping
    public ResponseEntity<Integer> create(@RequestBody SwimmingTest test) {
        repository.save(test);
        messagingTemplate.convertAndSend("/topic/swimmingTests", "New swimming test added!");
        return new ResponseEntity<>(test.getId(), HttpStatus.CREATED);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Void> update(@PathVariable Integer id, @RequestBody SwimmingTest test) {
        test.setId(id);
        repository.update(test);
        messagingTemplate.convertAndSend("/topic/swimmingTests", "Swimming test updated!");
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Integer id) {
        repository.delete(id);
        messagingTemplate.convertAndSend("/topic/swimmingTests", "Swimming test deleted!");
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
}
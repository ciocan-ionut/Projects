package validators;

import domain.person.Persoana;
import exceptions.ValidationException;

import java.time.LocalDate;

public class PersonValidator implements Validator<Persoana> {
    public void validate(Persoana p) throws ValidationException {
        if (p == null)
            throw new ValidationException("Null object!");
        if (p.getUsername() == null || p.getUsername().isBlank())
            throw new ValidationException("Username required!");
        if (p.getEmail() == null || !p.getEmail().contains("@"))
            throw new ValidationException("Invalid email!");
        if (p.getDob() == null || p.getDob().isAfter(LocalDate.now()))
            throw new ValidationException("Invalid birth date!");
        double e = p.getEmpathy();
        if (e < 0 || e > 10)
            throw new ValidationException("Invalid empathy value!");
    }
}

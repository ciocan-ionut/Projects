package validators;

import exceptions.ValidationException;

public interface Validator<TElem> {
    void validate(TElem entity) throws ValidationException;
}

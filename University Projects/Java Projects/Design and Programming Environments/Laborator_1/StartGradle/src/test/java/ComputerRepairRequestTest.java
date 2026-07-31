import model.ComputerRepairRequest;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class ComputerRepairRequestTest {
    private final ComputerRepairRequest emptyRequest = new ComputerRepairRequest();
    private final ComputerRepairRequest filledRequest = new ComputerRepairRequest(1,"A A","Address A","072222","Asus","13/10/2020","Broken display");

    @Test
    @DisplayName("Test for owner name")
    public void testOwnerName() {
        assertEquals("", emptyRequest.getOwnerName());
        assertEquals("A A", filledRequest.getOwnerName());
    }

    @Test
    @DisplayName("Test for owner address")
    public void testOwnerAddress() {
        assertEquals("", emptyRequest.getOwnerAddress());
        assertEquals("Address A", filledRequest.getOwnerAddress());
    }
}

package rjm.romek.finance.scraper;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;
import java.util.Map;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

class GoogleGrabberTest {

    private Grabber googleGrabber;

    @BeforeEach
    public void setUp() {
        googleGrabber = new GoogleGrabber("google+share+price");
    }

    @Test
    public void testPrice() throws IOException {
        Map<Date, MonetaryAmount> dateMonetaryAmountMap = googleGrabber.grabPrice();
        Optional<MonetaryAmount> first = dateMonetaryAmountMap.values().stream().findFirst();

        assertEquals(1, dateMonetaryAmountMap.size());
        assertTrue(first.isPresent());
        assertEquals("USD", first.get().getCurrency().getCurrencyCode());
    }
}
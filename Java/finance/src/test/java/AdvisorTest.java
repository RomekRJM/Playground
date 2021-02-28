import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.scraper.Grabber;
import rjm.romek.finance.notifier.Notifier;

import javax.money.Monetary;
import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;
import java.util.Map;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class AdvisorTest {

    @Mock
    private Notifier notifier;

    @Mock
    private Alert alert;

    @Mock
    private Grabber grabber;

    private Map<Date, MonetaryAmount> priceInTime = Map.of(
            createDate(14, 14, 0), createDollars(1),
            createDate(14, 15, 0), createDollars(2),
            createDate(14, 16, 0), createDollars(3)
    );

    private Advisor advisor;

    @BeforeEach
    public void setUp() throws IOException {
        MockitoAnnotations.openMocks(this);
        advisor = new Advisor(notifier);
        when(grabber.grabPrice()).thenReturn(priceInTime);
    }

    @Test
    public void shouldTriggerAlert() throws IOException {
        when(alert.isTriggered(any(), any())).thenReturn(true);

        advisor.check(grabber, alert);

        verify(notifier, times(1)).notify(any(), any(), any());
    }

    @Test
    public void shouldNotTriggerAlert() throws IOException {
        when(alert.isTriggered(any(), any())).thenReturn(false);

        advisor.check(grabber, alert);

        verify(notifier, times(0)).notify(any(), any(), any());
    }

    private static MonetaryAmount createDollars(int amount) {
        return Monetary.getDefaultAmountFactory()
                .setCurrency("USD").setNumber(amount).create();
    }

    private static Date createDate(int hours, int minutes, int seconds) {
        return new Calendar.Builder()
                .setDate(2045, 2, 12)
                .setTimeOfDay(hours, minutes, seconds)
                .build().getTime();
    }
}
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.io.IOException;
import java.util.Date;
import java.util.Map;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import rjm.romek.finance.DateUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.Notifier;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

class AdvisorTest {

  @Mock
  private Notifier notifier;

  @Mock
  private Alert alert;

  @Mock
  private Grabber grabber;

  private Map<Date, MonetaryAmount> priceInTime = Map.of(
      DateUtil.createDate(14, 14, 0), createDollars(1),
      DateUtil.createDate(14, 15, 0), createDollars(2),
      DateUtil.createDate(14, 16, 0), createDollars(3)
  );

  private Advisor advisor;

  @BeforeEach
  public void setUp() throws IOException, CouldNotGrabPriceException {
    MockitoAnnotations.openMocks(this);
    advisor = new Advisor(notifier);
    when(grabber.grabPrice()).thenReturn(priceInTime);
  }

  @Test
  public void shouldTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(alert.checkTrigger(Map.of(any(), any()))).thenReturn(true);

    advisor.check(grabber, alert);

    verify(notifier, times(1)).notify(any(), any(), any());
  }

  @Test
  public void shouldNotTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(alert.checkTrigger(Map.of(any(), any()))).thenReturn(false);

    advisor.check(grabber, alert);

    verify(notifier, times(0)).notify(any(), any(), any());
  }

  private static MonetaryAmount createDollars(int amount) {
    return Monetary.getDefaultAmountFactory()
        .setCurrency("USD").setNumber(amount).create();
  }

}
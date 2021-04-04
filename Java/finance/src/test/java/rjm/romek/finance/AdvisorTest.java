package rjm.romek.finance;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyMap;
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
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

class AdvisorTest {

  @Mock
  private EmailNotifier notifier;

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
    advisor = new Advisor(notifier, grabber, "", alert, "@yearly");
    when(grabber.grabPrice()).thenReturn(priceInTime);
  }

  @Test
  public void shouldTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(alert.checkTrigger(anyMap())).thenReturn(true);

    advisor.check();

    verify(notifier, times(1)).notify(any(), any());
  }

  @Test
  public void shouldNotTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(alert.checkTrigger(anyMap())).thenReturn(false);

    advisor.check();

    verify(notifier, times(0)).notify(any(), any());
  }

  private static MonetaryAmount createDollars(int amount) {
    return Monetary.getDefaultAmountFactory()
        .setCurrency("USD").setNumber(amount).create();
  }

}
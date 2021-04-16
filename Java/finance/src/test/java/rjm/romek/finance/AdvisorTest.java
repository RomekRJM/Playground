package rjm.romek.finance;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.SortedMap;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import org.assertj.core.util.Lists;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.persistency.DataPoint;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.rule.Rule;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@SpringBootTest
class AdvisorTest {

  @MockBean
  private EmailNotifier notifier;

  @Mock
  private Grabber grabber;

  private Rule rule = new PriceAboveRule(MonetaryDateUtil.getDollars(1));

  @Spy
  private Alert alert = new Alert(rule, 1);

  private SortedMap<Date, MonetaryAmount> priceInTime = MonetaryDateUtil
      .createDateMonetaryUnits("USD", 1, 2, 3);

  private final List<DataPoint> dataPoints = Lists.list(
      new DataPoint(1l, new Date(), "abcd", "USD", 1.0)
  );

  @BeforeEach
  public void setUp() throws IOException, CouldNotGrabPriceException {
    MockitoAnnotations.openMocks(this);
    when(grabber.grabPrice()).thenReturn(priceInTime);
  }

  @Test
  public void shouldTriggerAlert() throws IOException, CouldNotGrabPriceException {
    doReturn(true).when(alert).checkTrigger(dataPoints);

    new Advisor("recipient", grabber, "", alert, "@yearly").check();

    verify(notifier, times(1)).notify(any(), any());
  }

  @Test
  public void shouldNotTriggerAlert() throws IOException, CouldNotGrabPriceException {
    doReturn(false).when(alert).checkTrigger(dataPoints);

    new Advisor("recipient", grabber, "", alert, "@yearly").check();

    verify(notifier, times(0)).notify(any(), any());
  }

  private static MonetaryAmount createDollars(int amount) {
    return Monetary.getDefaultAmountFactory()
        .setCurrency("USD").setNumber(amount).create();
  }

}
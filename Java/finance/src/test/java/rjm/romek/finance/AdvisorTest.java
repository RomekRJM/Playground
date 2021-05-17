package rjm.romek.finance;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.reset;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.io.IOException;
import java.util.Date;
import java.util.SortedMap;
import javax.money.MonetaryAmount;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.context.ActiveProfiles;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.datapoint.model.DataPointRepository;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.notifier.model.NotificationRepository;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.rule.Rule;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@SpringBootTest
@ActiveProfiles(profiles = "test")
class AdvisorTest {

  @MockBean
  private EmailNotifier notifier;

  @Mock
  private Grabber grabber;

  @Autowired
  private DataPointRepository dataPointRepository;

  @Autowired
  private NotificationRepository notificationRepository;

  private Rule rule = new PriceAboveRule(MonetaryDateUtil.getDollars(1));

  private Alert alert = new Alert(rule, 2, 49);

  private SortedMap<Date, MonetaryAmount> priceInTimeMatchingRule = MonetaryDateUtil
      .createDateMonetaryUnits("USD", 0, 0,1, 2, 3);

  private SortedMap<Date, MonetaryAmount> priceInTimeNotMatchingRule = MonetaryDateUtil
      .createDateMonetaryUnits("USD", 1, 0, 1, 1, 2);

  private SortedMap<Date, MonetaryAmount> priceInTimeMatchingRuleAgain = MonetaryDateUtil
      .createDateMonetaryUnits("USD", 2, 0, 2, 2, 3);

  private static final String ADVISOR = "adv";
  private static final String [] RECIPIENTS = new String[] { "recipient@mail.com" };

  @BeforeEach
  public void setUp() {
    MockitoAnnotations.openMocks(this);
    dataPointRepository.deleteAll();
    dataPointRepository.flush();
    notificationRepository.deleteAll();
    notificationRepository.flush();
    reset(notifier);
  }

  @Test
  public void shouldTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(grabber.grabPrice()).thenReturn(priceInTimeMatchingRule);

    new Advisor(RECIPIENTS, grabber, ADVISOR, alert, "@yearly").check();

    verify(notifier, times(1)).notify(any(), any());
  }

  @Test
  public void shouldNotTriggerAlert() throws IOException, CouldNotGrabPriceException {
    when(grabber.grabPrice()).thenReturn(priceInTimeNotMatchingRule);

    new Advisor(RECIPIENTS, grabber, ADVISOR, alert, "@yearly").check();

    verify(notifier, times(0)).notify(any(), any());
  }

  @Test
  public void shouldRetrigger()
      throws IOException, CouldNotGrabPriceException, InterruptedException {
    Advisor advisor = new Advisor(RECIPIENTS, grabber, ADVISOR, alert, "@yearly");

    when(grabber.grabPrice()).thenReturn(priceInTimeMatchingRule);
    advisor.check();
    verify(notifier, times(1)).notify(any(), any());
    reset(notifier);

    Thread.sleep(50);

    when(grabber.grabPrice()).thenReturn(priceInTimeNotMatchingRule);
    advisor.check();
    verify(notifier, times(0)).notify(any(), any());
    reset(notifier);

    Thread.sleep(50);

    when(grabber.grabPrice()).thenReturn(priceInTimeMatchingRuleAgain);
    advisor.check();
    verify(notifier, times(1)).notify(any(), any());
  }

  @Test
  public void shouldNotRetriggerIfTooEarly()
      throws IOException, CouldNotGrabPriceException, InterruptedException {
    Advisor advisor = new Advisor(RECIPIENTS, grabber, ADVISOR, alert, "@yearly");

    when(grabber.grabPrice()).thenReturn(priceInTimeMatchingRule);
    advisor.check();
    verify(notifier, times(1)).notify(any(), any());
    reset(notifier);

    when(grabber.grabPrice()).thenReturn(priceInTimeMatchingRuleAgain);
    advisor.check();
    verify(notifier, times(0)).notify(any(), any());
  }

}
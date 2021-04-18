package rjm.romek.finance.alert;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import javax.money.MonetaryAmount;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import rjm.romek.finance.monetary.MonetaryConverter;
import rjm.romek.finance.monetary.MonetaryFactory;
import rjm.romek.finance.persistency.DataPoint;
import rjm.romek.finance.rule.Rule;

@Getter
@RequiredArgsConstructor
public class Alert {

  private final Rule rule;
  private final Integer occurrencesToActivate;

  public Alert() {
    this.rule = new Rule() {
      @Override
      public boolean applies(MonetaryAmount value) {
        return false;
      }
    };
    this.occurrencesToActivate = -1;
  }

  public boolean checkTrigger(final List<DataPoint> dataPoints) {
    int numberOfOccurrences = 0;
    List<DataPoint> sortedDataPoints = dataPoints.stream().sorted(Comparator.reverseOrder())
        .collect(Collectors.toList());
    MonetaryFactory monetaryFactory = new MonetaryFactory();

    for (DataPoint dataPoint : sortedDataPoints) {
      MonetaryConverter monetaryConverter = monetaryFactory.create(dataPoint.getCurrencyCode());
      if (rule
          .applies(monetaryConverter.convert(dataPoint.getCurrencyCode(), dataPoint.getValue()))) {
        ++numberOfOccurrences;
      } else {
        break;
      }
    }

    return occurrencesToActivate >= 0 && numberOfOccurrences >= occurrencesToActivate;
  }
}

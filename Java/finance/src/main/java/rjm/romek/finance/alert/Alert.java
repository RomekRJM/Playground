package rjm.romek.finance.alert;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import javax.money.MonetaryAmount;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
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
    this.occurrencesToActivate = 0;
  }

  public boolean checkTrigger(Map<Date, MonetaryAmount> map) {
    int numberOfOccurencies = 0;
    List<MonetaryAmount> amounts = new ArrayList<>(map.values());

    for (int i = amounts.size() - 1; i >= 0; --i) {
      if(rule.applies(amounts.get(i))) {
        ++numberOfOccurencies;
      } else {
        break;
      }
    }

    return numberOfOccurencies >= occurrencesToActivate;
  }
}

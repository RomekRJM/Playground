package rjm.romek.finance.alert;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import lombok.Getter;
import rjm.romek.finance.datapoint.model.DataPoint;
import rjm.romek.finance.monetary.MonetaryConverter;
import rjm.romek.finance.monetary.MonetaryFactory;
import rjm.romek.finance.rule.Rule;

@Getter
public class Alert {

  private final Rule rule;
  private final Integer occurrencesToActivate;
  private final Integer retriggerAfterMilliseconds;

  @JsonCreator
  public Alert(@JsonProperty("rule") Rule rule,
      @JsonProperty("occurrencesToActivate") Integer occurrencesToActivate,
      @JsonProperty("retriggerAfterMilliseconds") Integer retriggerAfterMilliseconds) {
    this.rule = rule;
    this.occurrencesToActivate = occurrencesToActivate;
    this.retriggerAfterMilliseconds = retriggerAfterMilliseconds;
  }

  public List<DataPoint> getRecentDataPointsTriggeringAlert(final List<DataPoint> dataPoints) {
    if (occurrencesToActivate <= 0 || dataPoints.size() == 0) {
      return Collections.emptyList();
    }

    MonetaryConverter monetaryConverter = new MonetaryFactory().create(dataPoints.get(0).getCurrencyCode());

    List<DataPoint> dataPointsReversed = dataPoints.stream()
        .sorted(Comparator.reverseOrder()).collect(Collectors.toList());

    Optional<DataPoint> firstNonMatching = dataPointsReversed.stream()
        .filter(dp -> !rule.applies(monetaryConverter.convert(dp.getCurrencyCode(), dp.getValue()))).findFirst();

    return firstNonMatching.isPresent() ?
        firstNonMatching.map(
            dataPoint -> dataPointsReversed.subList(0, dataPointsReversed.indexOf(dataPoint))).orElse(Collections.emptyList()
        ) : dataPointsReversed;

  }
}

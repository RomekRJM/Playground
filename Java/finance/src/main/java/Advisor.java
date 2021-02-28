import lombok.RequiredArgsConstructor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.grabber.Grabber;
import rjm.romek.finance.notifier.Notifier;

import java.util.Currency;
import java.util.Date;
import java.util.Map;
import java.util.stream.Collectors;

@RequiredArgsConstructor
public class Advisor {
    private Notifier notifier;

    public void check(Grabber grabber, Alert alert) {
        Map<Date, Currency> pricePoints = grabber.grabPrice();

        Map<Date, Currency> dataPointsWhenTriggered =
                pricePoints.entrySet().stream()
                        .filter(entry -> alert.isTriggered(entry.getKey(), entry.getValue()))
                        .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));

        if (dataPointsWhenTriggered.isEmpty()) {
            return;
        }

        notifier.notify("romek@example.com", alert, dataPointsWhenTriggered);
    }
}

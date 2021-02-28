package rjm.romek.finance.grabber;

import javax.money.MonetaryAmount;
import java.util.Date;
import java.util.Map;

public interface Grabber {
    Map<Date, MonetaryAmount> grabPrice();
}

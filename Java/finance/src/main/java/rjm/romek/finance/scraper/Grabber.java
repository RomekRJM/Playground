package rjm.romek.finance.scraper;

import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;
import java.util.Map;

public interface Grabber {

  Map<Date, MonetaryAmount> grabPrice() throws IOException, CouldNotGrabPriceException;
}

package rjm.romek.finance.scraper;

import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.Map;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import lombok.NoArgsConstructor;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

@NoArgsConstructor
public class GoogleGrabber extends Grabber {

  private static final String SEARCH_URL = "https://www.google.com/search?q=%s&ie=utf-8&oe=utf-8";
  private static final String QUERY_SEARCH_EXPRESSION = "g-card-section div g-card-section div span span span";

  public GoogleGrabber(String asset) {
    super(asset);
  }

  @Override
  public Map<Date, MonetaryAmount> grabPrice() throws IOException, CouldNotGrabPriceException {
    String assetSearchUrl = String.format(SEARCH_URL, asset);

    Document doc = Jsoup.connect(assetSearchUrl).get();

    return extractMonetaryData(doc);
  }

  private Map<Date, MonetaryAmount> extractMonetaryData(Document doc)
      throws CouldNotGrabPriceException {
    Elements elements = doc.select(QUERY_SEARCH_EXPRESSION);

    if (elements.size() < 2) {
      throw new CouldNotGrabPriceException("Not all required elements found in the response.");
    }

    List<Element> found = elements.subList(0, 2);

    return Map.of(
        new Date(),
        Monetary.getDefaultAmountFactory()
            .setCurrency(Monetary.getCurrency(getCurrency(elements.get(1))))
            .setNumber(getValue(elements.get(0)))
            .create()
    );
  }

  private Double getValue(Element element) throws CouldNotGrabPriceException {
    if (element.childNodes().isEmpty()) {
      throw new CouldNotGrabPriceException("Unable to parse the value from the response.");
    }

    String value = element.childNodes().get(0).toString()
        .replaceAll(",", "")
        .replaceAll("&nbsp;", "");

    return Double.valueOf(value);
  }

  private String getCurrency(Element element) throws CouldNotGrabPriceException {
    if (element.childNodes().isEmpty()) {
      throw new CouldNotGrabPriceException("Unable to parse the value from the response.");
    }

    return element.childNodes().get(0).toString().trim();
  }

}

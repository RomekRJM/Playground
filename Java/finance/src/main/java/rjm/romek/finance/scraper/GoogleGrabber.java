package rjm.romek.finance.scraper;

import java.io.IOException;
import java.util.Date;
import java.util.SortedMap;
import java.util.TreeMap;
import javax.money.MonetaryAmount;
import lombok.NoArgsConstructor;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import rjm.romek.finance.monetary.MonetaryConverter;
import rjm.romek.finance.monetary.MonetaryFactory;

@NoArgsConstructor
public class GoogleGrabber extends Grabber {

  private static final String SEARCH_URL = "https://www.google.com/search?q=%s&ie=utf-8&oe=utf-8";
  private static final String QUERY_SEARCH_EXPRESSION = "g-card-section div g-card-section div span span span";
  private static final String STATUS_SEARCH_EXPRESSION = "div[data-async-type='finance_wholepage_chart']";
  private static final MonetaryFactory MONETARY_FACTORY = new MonetaryFactory();

  public GoogleGrabber(String asset) {
    super(asset);
  }

  @Override
  public SortedMap<Date, MonetaryAmount> grabPrice() throws IOException, CouldNotGrabPriceException {
    String assetSearchUrl = String.format(SEARCH_URL, asset);
    Document doc = Jsoup.connect(assetSearchUrl).get();

    return extractMonetaryData(doc);
  }

  @Override
  public String grabGraphicalRepresentation() throws IOException {
    String assetSearchUrl = String.format(SEARCH_URL, asset);
    Document doc = Jsoup.connect(assetSearchUrl).get();
    Elements status = doc.select(STATUS_SEARCH_EXPRESSION);

    return status.first().html();
  }

  private SortedMap<Date, MonetaryAmount> extractMonetaryData(Document doc)
      throws CouldNotGrabPriceException {
    Elements elements = doc.select(QUERY_SEARCH_EXPRESSION);

    if (elements.size() < 2) {
      throw new CouldNotGrabPriceException("Not all required elements found in the response.");
    }

    SortedMap<Date, MonetaryAmount> map = new TreeMap<>();
    String unit = getUnit(elements.get(1));
    Double value = getValue(elements.get(0));
    MonetaryConverter monetaryConverter = MONETARY_FACTORY.create(unit);

    map.put(new Date(), monetaryConverter.convert(unit, value));

    return map;
  }

  Double getValue(Element element) throws CouldNotGrabPriceException {
    if (element.childNodes().isEmpty()) {
      throw new CouldNotGrabPriceException("Unable to parse the value from the response.");
    }

    String value = element.childNodes().get(0).toString()
        .replaceAll(",", "")
        .replaceAll("&nbsp;", "");

    return Double.valueOf(value);
  }

  String getUnit(Element element) throws CouldNotGrabPriceException {
    if (element.childNodes().isEmpty()) {
      throw new CouldNotGrabPriceException("Unable to parse the value from the response.");
    }

    return element.childNodes().get(0).toString().trim();
  }

}

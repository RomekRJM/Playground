package rjm.romek.finance.scraper;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;
import java.io.IOException;
import java.util.Date;
import java.util.SortedMap;
import java.util.TreeMap;
import javax.money.MonetaryAmount;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import rjm.romek.finance.monetary.MonetaryConverter;
import rjm.romek.finance.monetary.MonetaryFactory;

public class GoogleGrabber extends Grabber {

  private static final String SEARCH_URL = "https://www.google.com/search?q=%s";
  private static final String QUERY_SEARCH_EXPRESSION = "g-card-section div g-card-section div span span span";
  private static final MonetaryFactory MONETARY_FACTORY = new MonetaryFactory();
  private static final String LANGUAGE_HEADER = "Accept-Language";
  private static final String LANGUAGE = "en-US,en;q=0.9,pl;q=0.8";
  private static final String USER_AGENT_HEADER = "User-Agent";
  private static final String USER_AGENT = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.107 Safari/537.36";

  @JsonCreator
  public GoogleGrabber(@JsonProperty("asset") String asset) {
    super(asset);
  }

  @Override
  public SortedMap<Date, MonetaryAmount> grabPrice() throws IOException, CouldNotGrabPriceException {
    Document doc = Jsoup.connect(getUrl())
        .header(USER_AGENT_HEADER, USER_AGENT)
        .header(LANGUAGE_HEADER, LANGUAGE)
        .get();

    return extractMonetaryData(doc);
  }

  @Override
  public String getUrl() {
    return String.format(SEARCH_URL, asset);
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

    String value = element.childNodes().get(0).toString();

    return Double.valueOf(value.replaceAll(",", "").replaceAll(" ", "").replaceAll("&nbsp;", ""));
  }

  String getUnit(Element element) throws CouldNotGrabPriceException {
    if (element.childNodes().isEmpty()) {
      throw new CouldNotGrabPriceException("Unable to parse the value from the response.");
    }

    return element.childNodes().get(0).toString().trim();
  }

}

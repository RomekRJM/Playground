package rjm.romek.finance.scraper;

public class CouldNotGrabPriceException extends Exception {
  public CouldNotGrabPriceException(String problem) {
    super("There was a problem grabbing the value: " + problem);
  }
}

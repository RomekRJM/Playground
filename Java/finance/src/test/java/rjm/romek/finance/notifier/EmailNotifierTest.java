package rjm.romek.finance.notifier;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.icegreen.greenmail.spring.GreenMailBean;
import com.icegreen.greenmail.util.GreenMail;
import javax.mail.Message;
import javax.mail.MessagingException;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.Import;
import org.springframework.test.context.ActiveProfiles;

@SpringBootTest
@Import(GreenMailConfiguration.class)
@ActiveProfiles(profiles = "test")
class EmailNotifierTest {

  @Autowired
  private GreenMailBean greenMailBean;

  private GreenMail greenMail;

  @Value("${smtp.emailTo}")
  private String receiverUser;

  @Value("${smtp.password}")
  private String receiverPassword;

  @Value("${smtp.user}")
  private String senderUser;

  @Value("${smtp.password}")
  private String senderPassword;

  @Autowired
  private EmailNotifier emailNotifier;

  private static final String SUBJECT = "subject";
  private static final String BODY = "body";
  private final String [] recipients = new String[] { receiverUser };

  @BeforeEach
  public void setUp() {
    greenMail = greenMailBean.getGreenMail();
    greenMail.setUser(senderUser, senderPassword);
    greenMail.setUser(receiverUser, receiverPassword);
    greenMail.start();
  }

  @AfterEach
  public void tearDown() {
    greenMailBean.getGreenMail().stop();
  }

  @Test
  public void shouldSendEmail() throws MessagingException {
    emailNotifier.notify(recipients, new Notification(BODY, SUBJECT));
    assertMessageReceived(BODY, SUBJECT);
  }

  @Test
  public void shouldNotSendEmailOnConnectionError() {
    greenMail.stop();
    emailNotifier.notify(recipients, new Notification(BODY, SUBJECT));
    assertNoMessages();
  }

  private void assertMessageReceived(String body, String subject) throws MessagingException {
    assertTrue(greenMail.waitForIncomingEmail(5000, 1));
    Message message = greenMail.getReceivedMessages()[0];
    assertEquals(subject, message.getSubject());
  }

  private void assertNoMessages() {
    assertFalse(greenMail.waitForIncomingEmail(1000, 1));
    assertEquals(0, greenMail.getReceivedMessages().length);
  }
}
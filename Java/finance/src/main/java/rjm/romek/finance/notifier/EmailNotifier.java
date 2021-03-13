package rjm.romek.finance.notifier;

import java.util.Date;
import java.util.Map;
import java.util.Properties;
import javax.mail.Authenticator;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.money.MonetaryAmount;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import rjm.romek.finance.alert.Alert;

@Component
@Slf4j
public class EmailNotifier implements Notifier {

  private static final String SUBJECT = "Finance Alert";
  private static final String MESSAGE = "%s has been %s the price point %s for %s times in a row.";


  @Value("${SMTP_HOST}")
  private String smtpHost;

  @Value("${SMTP_PORT}")
  private String smtpPort;

  @Value("${SMTP_USER}")
  private String smtpUser;

  @Value("${SMTP_PASSWORD}")
  private String smtpPassword;

  @Override
  public void notify(String who, Alert what, Map<Date, MonetaryAmount> when) {

    sendEmail(getSession(), who, SUBJECT, MESSAGE, smtpUser);
  }

  private Session getSession() {
    Properties props = new Properties();
    props.put("mail.smtp.host", smtpHost);
    props.put("mail.smtp.port", smtpPort);
    props.put("mail.smtp.auth", "true");
    props.put("mail.smtp.starttls.enable", "true");
    props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
    props.put("mail.smtp.connectiontimeout", "3000");
    props.put("mail.smtp.timeout", "5000");

    Authenticator auth = new Authenticator() {
      protected PasswordAuthentication getPasswordAuthentication() {
        return new PasswordAuthentication(smtpUser, smtpPassword);
      }
    };
    return Session.getInstance(props, auth);
  }

  private static void sendEmail(Session session, String toEmail, String subject, String body,
      String from) {

    try {
      MimeMessage msg = new MimeMessage(session);
      msg.addHeader("Content-type", "text/HTML; charset=UTF-8");
      msg.addHeader("format", "flowed");
      msg.addHeader("Content-Transfer-Encoding", "8bit");

      msg.setFrom(new InternetAddress(from));
      msg.setReplyTo(InternetAddress.parse(from, false));
      msg.setSubject(subject, "UTF-8");
      msg.setText(body, "UTF-8");
      msg.setSentDate(new Date());

      msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(toEmail, false));
      Transport.send(msg, msg.getAllRecipients());

    } catch (MessagingException e) {
      log.error("Can't send the email: " + e.getMessage());
    }
  }

}

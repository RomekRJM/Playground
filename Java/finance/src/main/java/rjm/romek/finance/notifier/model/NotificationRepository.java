package rjm.romek.finance.notifier.model;

import java.util.Optional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface NotificationRepository extends JpaRepository<Notification, Long> {

  Optional<Notification> findTopByAdvisorNameEqualsAndAndRecipientEqualsOrderByDateDesc(
      String advisorName, String recipient);
}

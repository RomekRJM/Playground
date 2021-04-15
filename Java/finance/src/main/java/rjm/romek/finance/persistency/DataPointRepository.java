package rjm.romek.finance.persistency;

import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface DataPointRepository extends JpaRepository<DataPoint, Long> {

  List<DataPoint> findTop32DataPointsByAdvisorNameOrderByDateDesc(String advisorName);
}

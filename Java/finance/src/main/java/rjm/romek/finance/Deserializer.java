package rjm.romek.finance;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.List;

public class Deserializer {
  public Collection<Advisor> load(File file) throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());

    return mapper.readValue(file, new TypeReference<List<Advisor>>() {
    });
  }

  public void save(Collection<Advisor> advisors, File file) throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
    mapper.writeValue(file, advisors);
  }
}

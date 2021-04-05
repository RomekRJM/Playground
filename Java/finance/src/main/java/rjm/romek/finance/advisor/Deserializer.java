package rjm.romek.finance.advisor;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.List;
import org.springframework.core.io.support.PathMatchingResourcePatternResolver;
import org.springframework.stereotype.Component;

@Component
public class Deserializer {

  public static final String CONFIG_FILE = "jobs.yaml";
  private static final PathMatchingResourcePatternResolver RESOURCE_PATTERN_RESOLVER
      = new PathMatchingResourcePatternResolver();

  public Collection<Advisor> load() throws IOException {
    return load(CONFIG_FILE);
  }

  public Collection<Advisor> load(String filePath) throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());

    return mapper.readValue(getJobsDefinitionFile(filePath), new TypeReference<List<Advisor>>() {
    });
  }

  public void save(Collection<Advisor> advisors, File file) throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
    mapper.writeValue(file, advisors);
  }

  private File getJobsDefinitionFile(String filePath) throws IOException {
    return RESOURCE_PATTERN_RESOLVER.getResource(filePath).getFile();
  }
}

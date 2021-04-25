package rjm.romek.finance.advisor;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.List;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.io.ResourceLoader;
import org.springframework.stereotype.Component;

@Component
public class Deserializer {

  private final String configFile;

  ResourceLoader resourceLoader;

  public Deserializer(@Value("${jobs.file}") String configFile, ResourceLoader resourceLoader) {
    this.configFile = configFile;
    this.resourceLoader = resourceLoader;
  }

  public Collection<Advisor> load() throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());

    return mapper.readValue(getJobsDefinitionFile(configFile), new TypeReference<List<Advisor>>() {
    });
  }

  public void save(Collection<Advisor> advisors, File file) throws IOException {
    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
    mapper.writeValue(file, advisors);
  }

  private File getJobsDefinitionFile(String filePath) throws IOException {
    return resourceLoader.getResource(filePath).getFile();
  }
}

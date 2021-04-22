import lambdasandstreams.Hero;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Optional;
import java.util.function.Consumer;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class HeroTest {

    private ArrayList<Hero> heroes;

    @BeforeEach
    public void setUp() {
        heroes = new ArrayList<Hero>();
        heroes.add(new Hero("Gargantua", 5, 1));
        heroes.add(new Hero("Barrog", 150, 11));
        heroes.add(new Hero("Hossy", 35, 5));
        heroes.add(new Hero("Cubth", 250, 22));
    }

    @Test
    public void testHeroesFiltering() {
        assertEquals(heroes.stream().filter(x -> x.getLevel() > 1).count(), 3);
    }

    @Test
    public void testHeroesOrdering() {
        assertEquals(heroes.stream().sorted(Comparator.comparing(Hero::getName)).findFirst().get().getName(), "Barrog");
    }

    @Test
    public void testHeroesForEachWithFunctionalInterface() {
        Consumer<Hero> heroConsumer = x -> {
            x.setHp(x.getHp() + 100);
        };

        heroes.stream().forEach(heroConsumer::accept);

        assert(heroes.stream().allMatch(x -> x.getHp() > 100));
    }

    @Test
    public void testFindHeroesWithNamesFromFile() throws IOException {
        ArrayList<Hero>heroesWithNameFromFile = new ArrayList<Hero>();
        try (Stream<String> stream = Files.lines(Paths.get("src/test/resources/HeroesNames"))) {
            stream.forEach(x ->
            {
                Optional<Hero> optionalHero = heroes.stream().filter(y -> y.getName().equals(x)).findFirst();
                optionalHero.ifPresent(z -> heroesWithNameFromFile.add(z));
            }
            );
        } catch (IOException e) {
            throw e;
        }

        assert(heroesWithNameFromFile.get(0).getName().equals("Barrog"));
    }
}

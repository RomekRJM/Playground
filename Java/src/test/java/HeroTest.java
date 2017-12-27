import static org.junit.jupiter.api.Assertions.assertEquals;

import lambdasandstreams.Hero;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.function.Consumer;

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
}

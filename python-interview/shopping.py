# As we work in online grocery we would like you to compute discount for our clients
# Each client is identified by his name and has list of shoppings assigned to him:
#
# shoppings = [
#    Shoppings("Victor", [12.2, 21]),
#    Shoppings("Jane", [5.5, 5.1, 5.8, 6.3]),
#    Shoppings("Adam", [5, 8, 9]),
#    Shoppings("Sarah", [20.3, 11.5]),
#]
#
# 1. Define shopping class.
# 2. Compute average amount of money, that our clients spent.
# 3. Filter out these clients, which spent more, than average.
# 4. Compute 10% discount for each client, that spent more, than average.
# 5. Write your findings to a file, having format:
#
#   client_name1: discount1
#   client_name2: discount2


class Shopping():
    def __init__(self, name, paid):
        self.name = name
        self.paid = paid

    def total(self):
        return sum(self.paid)

shoppings = [
    Shopping("Victor", [12.2, 21]),
    Shopping("Jane", [5.5, 5.1, 5.8, 6.3]),
    Shopping("Adam", [5, 8, 9]),
    Shopping("Sarah", [20.3, 11.5]),
]

avg = sum(map(lambda x: x.total(), shoppings)) / len(shoppings)
who = filter(lambda x: x.total() > avg, shoppings)

with open("test", "w") as f:
    for w in who:
        f.write("%s: %s\n" % (w.name, w.total()*0.1))

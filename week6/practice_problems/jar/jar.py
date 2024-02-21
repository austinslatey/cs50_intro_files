class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return f"Jar(capacity={self.capacity}, size={self._size})"

    def deposit(self, n):
        if self._size + n <= self._capacity:
            self._size += n
            print(f"Deposited {n} items into the jar.")
        else:
            print(f"Not enough capacity to deposit {n} items in jar")

    def withdraw(self, n):
        if self._size >= n:
            self._size -= n
            print(f"Withdrew {n} items from the jar.")
        else:
            print("Not enough items in jar to withdraw")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar()
    print(str(jar.capacity))

    print(str(jar))

    jar.deposit(2)
    print(str(jar))


if __name__ == "__main__":
    main()
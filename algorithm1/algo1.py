# Carlos Lopez, Ryan Monte, Angel Penaloza, Boushra Bettir
# Algorithm 1: Connecting Pairs of Persons

class PairSwapper:
    def __init__(self) :
        self.position = {} #keeps track of current index
        self.count = 0 #counter which holds num of swaps made

    def minSwaps(self, row):
        position = self.position

        #store each index of row in position dictionary
        for i in range(len(row)) :
            position[row[i]] = i

        #iterating over pair of elements
        for n in range(len(row) // 2) :
            #(2*n) and (2*n+1) since we want to look at first and second element of each pair
            first = row[2*n]
            second = row[2*n + 1]

            #this statement checks to see if elements are in the right order
            #for even first, second must be first + 1, else first - 1
            if (first % 2 == 0 and second != first + 1) or (first % 2 == 1 and second != first - 1):
                #if first element is even, find target pos for next odd number
                if first % 2 == 0:
                    target = position[first + 1] #position of next odd element
                else:
                    target = position[first - 1] #position of previous first element of pair

                row[2*n+1], row[target] = row[target], row[2*n+1]

                # Update positions in dictionary after swapping, every iteration
                position[row[2*n+1]] = 2*n+1
                position[row[target]] = target

                self.count += 1 #increments swap count

        return self.count #returns total number of swaps

def main():
    example_row = [1, 3, 2, 0, 4, 6, 5, 7]
    swap = PairSwapper()
    swap_count = swap.minSwaps(example_row)
    print("Output:", swap_count)


if __name__ == "__main__":
    main()
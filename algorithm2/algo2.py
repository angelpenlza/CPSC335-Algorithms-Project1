def find_preferred_starting_city(city_distances, fuel, mpg):
    """
    This function returns the index of the preferred starting city such that
    you can travel to all cities and return to the starting city without running out of fuel.

    Parameters:
    - city_distances: List of integers, where city_distances[i] is the distance from city i to city i+1.
    - fuel: List of integers, where fuel[i] is the amount of fuel available at city i.
    - mpg: Integer, the number of miles that can be driven per gallon of fuel.

    Returns:
    - Integer: The index of the preferred starting city.
    """

    n = len(city_distances)  # Number of cities

    total_fuel = 0  # Total fuel gained across the journey
    total_distance = 0  # Total distance to be covered
    current_fuel = 0  # Fuel balance as we travel between cities
    start_city = 0  # The city from where we start the journey

    # Traverse through all the cities
    for i in range(n):
        # Calculate fuel gained and distance to the next city
        fuel_gained = fuel[i] * mpg
        distance_to_next = city_distances[i]

        # Update total fuel and total distance counters
        total_fuel += fuel_gained
        total_distance += distance_to_next

        # Update current fuel balance
        current_fuel += fuel_gained - distance_to_next

        # If at any point current fuel is negative, reset the start city
        if current_fuel < 0:
            # Move the start city to the next city
            start_city = i + 1

            # Reset current fuel balance
            current_fuel = 0

    # After the loop, check if total fuel is enough to cover the total distance
    if total_fuel >= total_distance:
        return start_city
    else:
        return -1  # Should never happen according to the problem description (guaranteed valid solution)


# Function to get user input
def get_user_input():
    print("Enter the city distances (separated by spaces):")
    city_distances = list(map(int, input().split()))

    print("Enter the amount of fuel at each city (separated by spaces):")
    fuel = list(map(int, input().split()))

    print("Enter the number of miles per gallon (mpg):")
    mpg = int(input())

    # Ensure the number of fuel values matches the number of distance values
    if len(city_distances) != len(fuel):
        print("Error: The number of fuel values should match the number of distances.")
        return None, None, None

    return city_distances, fuel, mpg


# Main execution function
def main():
    city_distances, fuel, mpg = get_user_input()

    if city_distances and fuel and mpg:  # Ensure input is valid
        preferred_city = find_preferred_starting_city(city_distances, fuel, mpg)
        print(f"The preferred starting city is: {preferred_city}")
    else:
        print("Invalid input, please try again.")


# Run the program
if __name__ == "__main__":
    main()

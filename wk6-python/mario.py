def main():
    # Get user input for the height of pyramid
    height = get_height()
    # Set loop for rows of both pyramids (building from top to bottom)
    for row in range(height):
        # Set loop for columns of first pyramid
        for colOne in range(height):
            if row + colOne >= height - 1:
                print('#', end="")
            else:
                print(' ', end="")
        print('  ', end="")
        # Set loop for columns of second pyramid
        # Start at height - 1, go to 0 inclusive, decrement by 1
        for colTwo in range(height - 1, -1, -1):
            if row + colTwo >= height - 1:
                print('#', end="")
        print('')


def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                return height
            else:
                print("Pick a height between 1 and 8.")
        except ValueError:
            print("Please type an integer.")


main()
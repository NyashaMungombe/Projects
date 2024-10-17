# Function to sort the scores in ascending order
def sort_scores(scores):
    n = len(scores)
    for i in range(n):
        for j in range(0, n-i-1):
            if scores[j] > scores[j+1]:
                # Swap if the element is greater than the next
                scores[j], scores[j+1] = scores[j+1], scores[j]

# Function to calculate the average score
def calculate_average(scores):
    total = sum(scores)
    return total / len(scores) if len(scores) > 0 else 0

# Main function to run the program
def main():
    # Get the number of test scores from the user
    num_scores = int(input("Enter the number of test scores: "))

    # Dynamically allocate memory for the scores
    scores = []

    # Input the test scores
    for i in range(num_scores):
        score = float(input(f"Enter score {i + 1}: "))
        scores.append(score)  # Use append to mimic dynamic allocation

    # Sort the scores
    sort_scores(scores)

    # Calculate the average
    average = calculate_average(scores)

    # Display the sorted scores and the average
    print("\nSorted List of Scores:")
    for score in scores:
        print(f"{score:.2f}")

    print(f"\nAverage Score: {average:.2f}")

# Run the program
if __name__ == "__main__":
    main()

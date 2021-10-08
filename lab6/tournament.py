# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")


    teams = []
    team_names = []
    #Read teams into memory from file:
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            teams.append(row)
        for dict in teams:
            dict["rating"] = int(dict["rating"])
            team_names.append(dict["team"])


    # Simulate N tournaments and keep track of win counts
    counts = {}

    #setting the values of all the keys to zero
    for team_name in team_names:
        counts[team_name] = 0
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners

def power(base, result):
    counter = 0
    while True:

        if result == 1:
            break
        result = result/base
        counter += 1
    return counter

def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    clone = teams
    teamNames = []
    for i in range(power(2, len(clone))):
        clone = simulate_round(clone)
    for item in clone:
        winner = item["team"]
    return winner

if __name__ == "__main__":
    main()

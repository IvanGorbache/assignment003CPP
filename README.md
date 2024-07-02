### Catan Class
The `Catan` class represents a Catan game instance.

- **Attributes:**
  - `players`: Array of pointers to `Player` objects representing the players in the game.
  - `turnCounter`: Array tracking the turn count for each player.
  - `originalMap`: 2D array storing the initial state of the game map.
  - `map`: 2D array of `Point` objects representing the game map.
  - `currentTurn`: Integer indicating the current player's turn.
  - `knightsCount`, `victoryCardCount`: Counters for game-specific metrics for checks to ensure that there are at most 3 knights and 5 victory cards
  - `minCard`, `maxCard`: Min and max card values for random card generation to ensure that there are at most 3 knights and 5 victory cards

- **Methods:**
  - `rollDice(int cheat)`: Simulates rolling dice. Cheat is used when we want to role a specfic value.
  - `placeSettlement(Point a)`: Places a settlement on the map.
  - `buildCity(Point a)`: Upgrades a settlement to a city.
  - `placeRoad(Point a, Point b, bool isFree)`: Constructs a road between two points.
  - `trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount)`: Facilitates resource trading between players.
  - `buyDevelopmentCard(int choice)`: Allows a player to buy a development card.
  - `useDevelopmentCard(int card, int resource, ...params)`: Uses a development card with specified parameters.
  - `checkVictory()`: Checks if a player has achieved victory.
  - `endTurn()`: Ends the current player's turn.
  - `printMap() const`: Prints the game map.
  - `GetPoint(int x, int y) const`: Retrieves a `Point` object from the map.
  - `getPlayer(int index) const`: Retrieves a pointer to a `Player` object by index.

### Player Class
The `Player` class represents a player in the Catan game.

- **Attributes:**
  - `victoryPoints`: Integer tracking the player's victory points.
  - `name`: String representing the player's name.
  - `settlements`: Vector of `Point` objects representing the player's settlements.
  - `resources`: Array of integers representing the player's resources.
  - `totalResources`: Total count of the player's resources.

- **Methods:**
  - `getTotalResources() const`: Retrieves the total count of resources.
  - `getVictoryPoints() const`: Retrieves the player's victory points.
  - `getSettlements() const`: Retrieves a vector of settlements.
  - `canTrade(int resourceType, int amount)`: Checks if the player can trade resources.
  - `modifyResources(int myResource, int myAmount)`: Modifies the player's resources.
  - `getResourceCount(int resourceType)`: Retrieves the count of a specific resource type.
  - `modifyVictoryPoints(int count)`: Modifies the player's victory points.
  - `addSettlements(Point settlements)`: Adds a settlement to the player's holdings.
  - `getName() const`: Retrieves the player's name.
  - `printer()`: Prints player information.

### Point Class
The `Point` class represents a location on the Catan game map.

- **Attributes:**
  - `id`: Integer ID of the point.
  - `x`, `y`: Coordinates of the point.
  - `owner`: Pointer to the `Player` who owns the point.
  - `classification`: Integer classification of the point.
  - `neighbors`: Vector of neighboring `Point` objects.
  - `roads`: Vector of `Road` objects associated with the point.

- **Methods:**
  - `getX() const`, `getY() const`, `getId() const`: Accessors for point attributes.
  - `getOwner() const`, `getNeighbors() const`, `getClassification() const`: Accessors for relationships and classifications.
  - `setID(int id)`, `setOwner(Player *p)`, `setClassification(int classification)`: Mutators for point attributes.
  - `addNeighbor(Point &newNeighbor)`: Adds a neighboring point.
  - `isNeighbor(Point a)`: Checks if a point is a neighbor.
  - `upgrade()`: Upgrades the point's classification.
  - `operator==(const Point& other) const`: Equality operator for points.
  - `addRoad(Road road)`: Adds a road associated with the point.
  - `getRoads() const`: Retrieves roads associated with the point.
  - `hasRoad(Point b)`: Checks if there is a road to a neighboring point.

### Road Class
The `Road` class represents a road connecting two points on the Catan game map.

- **Attributes:**
  - `owner`: Pointer to the `Player` who owns the road.
  - `start`, `end`: Pointers to the starting and ending `Point` of the road.

- **Methods:**
  - `getOwner() const`, `setOwner(Player *p)`: Accessors and mutator for the road's owner.
  - `getStart() const`, `getEnd() const`: Accessors for the starting and ending points of the road.
  - `toString() const`: Converts the road to a string representation.

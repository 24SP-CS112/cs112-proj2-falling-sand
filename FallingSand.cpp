#include <NonBlockingGame.h>

#include <chrono>
#include <iostream>
#include <random>

using namespace bridges::game;
using namespace std;

/**
 * Welcome to Bridges Falling Sands Game Assignment.
 *
 * The "container" that your elements will be moving around in is a 2D array
 * visualized as a game grid.
 *
 * Try to make the elements react to each other as they would in real life using
 * conditional statements.
 *
 * For example, WATER in a cell should fall down on the condition that the cell
 * below it is empty. Consider how the water should behave if the cell below it
 * is metal.
 *
 * Also consider sand falling into a container of water. In real life, the water
 * will rise and sand will fall through it to the bottom of the container. What
 * kind of movement would values in a 2D array have to make to mirror that
 * behavior?
 *
 * Move your cursor around the grid with the arrow keys.
 *
 * Elemental variable names are as follows: (select the element with the
 * corresponding key) METAL (A key), WATER (W key), SAND  (S key), DELETE (D
 * key), EMPTY (Empty Cell, after an element moves out of it or is deleted)
 *
 * Q key refreshes the game grid using the newGame() function.
 */
struct FallingSand : public NonBlockingGame {
    // Your grid can contain up to 1024 cells.
    // The largest square grid available is 32 x 32
    static const int GRID_COLUMNS = 30;
    static const int GRID_ROWS = 30;

    // Element values
    static const int EMPTY = 0;
    static const int METAL = 1;
    static const int SAND = 2;
    static const int WATER = 3;
    static const int DELETE = 4;

    // Element colors
    static const NamedColor EMPTY_COLOR = NamedColor::black;
    static const NamedColor METAL_COLOR = NamedColor::gray;
    static const NamedColor SAND_COLOR = NamedColor::sandybrown;
    static const NamedColor WATER_COLOR = NamedColor::blue;
    static const NamedColor DELETE_COLOR = NamedColor::red;

    // Element symbols
    static const NamedSymbol EMPTY_SYMBOL = NamedSymbol::none;
    static const NamedSymbol METAL_SYMBOL = NamedSymbol::square;
    static const NamedSymbol SAND_SYMBOL = NamedSymbol::waves;
    static const NamedSymbol WATER_SYMBOL = NamedSymbol::droplet;

    // An array that maps the location of each element
    int container[GRID_ROWS][GRID_COLUMNS];

    NamedSymbol cursorSymbol = NamedSymbol::star;
    NamedColor cursorColor = NamedColor::gray;
    int cursor = METAL;

    // Used to control the game's frame rate.
    long FRAMERATE = 1000000000 / 15;
    std::chrono::time_point<std::chrono::high_resolution_clock> frameTime =
        std::chrono::high_resolution_clock::now();

    // Initial location of the cursor on the grid.
    int cursorRow = 10;
    int cursorCol = 10;

    FallingSand(int assID, std::string username, std::string apikey)
        : NonBlockingGame(assID, username, apikey, GRID_COLUMNS, GRID_ROWS) {
        setDescription(
            "Simulate elemental reactions and gravity within a grid. Use the "
            "arrow keys to move your cursor. Alternate elements with the A, S, "
            "D, and W keys. Press space to place an element at the cursors "
            "location.");
        setTitle("Falling Sand");
    }

    // The initialize function runs once before the game loop begins.
    // Assign your game variables here.
    virtual void initialize() override {
        srand(time(NULL));

        keyUpSetupFire(10);
        keyLeftSetupFire(10);
        keyDownSetupFire(10);
        keyRightSetupFire(10);
        keySpaceSetupFire(10);

        /* TODO: loop through entire container grid, initializing each
           cell to EMPTY. */

        // Default starting configurtion, feel free to change it or remove it
        // entirely shape 1
        container[10][5] = METAL;
        container[11][5] = METAL;
        container[12][5] = METAL;
        container[12][6] = METAL;
        container[12][7] = METAL;
        container[12][8] = METAL;
        container[11][8] = METAL;
        container[10][8] = METAL;
        container[9][8] = METAL;
        // shape 2
        container[17][9] = METAL;
        container[18][9] = METAL;
        container[19][9] = METAL;
        container[20][9] = METAL;
        container[21][9] = METAL;
        container[21][10] = METAL;
        container[21][11] = METAL;
        container[21][12] = METAL;
        container[21][13] = METAL;
        container[20][13] = METAL;
        container[19][13] = METAL;
        container[18][13] = METAL;
        container[17][13] = METAL;
        container[16][13] = METAL;
        container[15][13] = METAL;
        container[14][13] = METAL;
        // shape 3
        container[3][13] = METAL;
        container[4][13] = METAL;
        container[5][13] = METAL;
        container[6][13] = METAL;
        container[7][13] = METAL;
        container[8][13] = METAL;
        container[9][13] = METAL;
        container[10][13] = METAL;
        container[10][14] = METAL;
        container[10][15] = METAL;
        container[10][16] = METAL;
        container[10][17] = METAL;
        container[10][18] = METAL;
        container[10][19] = METAL;
        container[13][20] = METAL;
        // end starting config
    }

    // Required method that runs continously while the game is being played.
    // Place game functions in the order they must operate here.
    virtual void gameLoop() override {
        controls();    // User input
        paintBoard();  // Updates game display

        // Runs when it's time for the next frame.
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - frameTime)
                .count() > FRAMERATE) {
            frameTime = std::chrono::high_resolution_clock::now();

            /**
             * TODO
             * Loop through the container array from bottom to top, per column.
             * (i.e., for column 0, go from bottom to top, then column 1, bottom
             * to top, then column 2 ...) Inside the inner loop, use a switch
             * statement to determine which kind of cell it is (WATER, METAL, or
             * SAND) and call the appropriate behavior function.
             */
        }
    }

    // Logic for metal in the grid -- does nothing but "stick" to the background
    void metalBehavior(int row, int col) {}

    // Logic for water in the grid
    void waterBehavior(int row, int col) {
        /**
         * TODO:
         * if the cell is not on the bottom row, then
         *  if the cell below this one is EMPTY, then make this cell
         *    empty, and place WATER in the cell below.
         *  else:
         *    if the cell to the left AND the cell to the right are both EMPTY,
         *      clear this cell.
         *      pick a random number -- either 0 or 1. 0 represents left, and
         *        1 represents right.  Use rand() and the modulo operator.
         *      if the random number is 0, place the WATER to in the cell to the left,
         *      else place it in the cell to the right.
         *    else if cell to the left is EMPTY,
         *      clear this cell and place WATER in the cell to the left.
         *    else  if cell to the right is EMPTY,
         *      similar for the cell to the right.
         */
    }

    // Logic for sand in the grid
    void sandBehavior(int row, int col) {
        // TODO:
        // Basic sand behavior example. If cell below is empty, sand falls down.
        // If the cell below contains water, the water moves up and sand moves
        // down.
        // Call clearElement() and placeElement() (possibly multiple times)
    }

    /**
     * Keyboard Controls.
     *
     * Move the cursor around with the arrow keys.
     *
     * Register a click with Spacebar.
     *
     * Element type can be changed with the W, S, A, D keys.
     * akey = metal
     * skey = sand
     * dkey = delete
     * wkey = water
     **/
    void controls() {
        if (keyAFire()) {
            cursorColor = METAL_COLOR;
            cursor = METAL;
        } else if (keyWFire()) {
            cursorColor = WATER_COLOR;
            cursor = WATER;
        } else if (keySFire()) {
            cursorColor = SAND_COLOR;
            cursor = SAND;
        } else if (keyDFire()) {
            cursorColor = DELETE_COLOR;
            cursor = DELETE;
        } else if (keyLeftFire() && cursorCol > 0) {
            cursorCol = cursorCol - 1;
        } else if (keyRightFire() && cursorCol < GRID_COLUMNS - 1) {
            cursorCol = cursorCol + 1;
        } else if (keyUpFire() && cursorRow > 0) {
            cursorRow = cursorRow - 1;
        } else if (keyDownFire() && cursorRow < GRID_ROWS - 1) {
            cursorRow = cursorRow + 1;
        } else if (keyQFire()) {
            newGame();
        } else if (keySpaceFire()) {
            if (cursor == DELETE) {
                clearElement(cursorRow, cursorCol);
            } else {
                placeElement(cursor, cursorRow, cursorCol);
            }
        }
    }

    // Place specific element at a location on the grid at specified col/row.
    void placeElement(int element, int row, int col) {
        container[row][col] = element;
    }

    // Clears an element from the grid.
    void clearElement(int row, int col) {
        container[row][col] = EMPTY;
    }

    void newGame() {
        for (int i = 0; i < GRID_ROWS; i++) {
            for (int j = 0; j < GRID_COLUMNS; j++) {
                container[i][j] = EMPTY;
            }
        }
        initialize();
        cursorRow = 10;
        cursorCol = 10;
        paintBoard();
    }

    // Adds color and symbols to cells in grid based on values in the 2D array.
    void paintBoard() {
        // TODO:
        // loop through the container grid from top to bottom.
        //   in the body of the inner loop, use a switch statement on
        //     container[row][col]. If the element is SAND, call
        //     drawSymbol() appropriately, with SAND_SYMBOL and SAND_COLOR.
        //     Do similarly for WATER, METAL, and EMPTY.


        drawSymbol(cursorRow, cursorCol, cursorSymbol, cursorColor);
    }
};

//
// Pass your bridges username and bridges API key as arguments at runtime: e.g.:
// ./FallingSand VictorNorman 12345678890
int main(int argc, char** argv) {
    FallingSand game(115, argv[1], argv[2]);
    game.start();
}

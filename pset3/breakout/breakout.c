//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// height and width of paddle in radius
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 60

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // x and y ball velocity
    int maxVelocity = 3;
    int minVelocity = -3;
    int xVelocity = ((maxVelocity - minVelocity) * drand48() + minVelocity) ;
    int yVelocity = 2;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        
        // move the ball
        move(ball, xVelocity, yVelocity);

        
        // Bounce the ball off the window edges
        // Get (x, y) of the ball
        int xBall = getX(ball);
        int yBall = getY(ball);

        // Bounce off Vertical edges of window
        if ((xBall + 2 * RADIUS >= WIDTH) || (xBall <= 0))
            xVelocity *= -1;
        // Bound off Horizontal edges 
        if ((yBall + 2 * RADIUS >= HEIGHT) || (yBall <= 0))
            yVelocity *= -1;

        // detect collision with paddle or a brick
        GObject object = detectCollision(window, ball);
        if (object != NULL) 
        {
            // collision with the paddle
            if (object == paddle)
                yVelocity *= -1;
            
            // collision  with a brick
            else if (strcmp(getType(object), "GRect") == 0)
            {
                yVelocity *= -1;
                removeGWindow(window, object);
                bricks --;
            }
        }   
        pause(10);
        // wait for event
        GMouseEvent event = getNextEvent(MOUSE_EVENT);
                            
        // if we heard one
        if (event != NULL)
        {
            // Control the paddle movement with the mouse
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = (getX(event) - PADDLE_WIDTH / 2) ;
                double y = getY(paddle) ;

                // Restrict the paddle movement to the game window
                if (x + PADDLE_WIDTH > WIDTH)
                    x = WIDTH - PADDLE_WIDTH;
                else if (x < 0)
                    x = 0;
                setLocation(paddle, x, y);
            }
        }   

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Define the colors to be used for each row
    // Colors will repeat once all of them are used
    char* colors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN", "GRAY", "MAGENTA", "PINT"};

    // Compute brick width and height based on the numbers of ROWS & COLS
    const int BRICK_WIDTH = WIDTH / COLS - COLS / 2 ;
    const int BRICK_HEIGHT = PADDLE_HEIGHT;

    // Compute the white space between bricks
    const int SHIFT = (WIDTH - COLS * BRICK_WIDTH)/ COLS ;

    // Compute the Horizontal axis offset so the bricks grid is centered
    const int XOFFSET = (WIDTH - COLS * (SHIFT + BRICK_WIDTH) + SHIFT) / 2;

    // Define the Vertical axis offset so that bricks are not too high
    const int YOFFSET = 50;

    // 2D bricks array (Brick Grid)
    GRect bricks[ROWS][COLS];

    // Layout the bricks
    for (int i = 0; i < ROWS; i++)
    {
        int yLocation = (BRICK_HEIGHT + SHIFT) * i + YOFFSET;

        for (int j = 0; j < COLS; j++)
        {
            int xLocation = (BRICK_WIDTH + SHIFT) * j + XOFFSET;
            bricks[i][j] = newGRect(xLocation, yLocation, BRICK_WIDTH, BRICK_HEIGHT); 
                
            // set brick fill color for row "i"
            setFilled(bricks[i][j], true);
            // modulus is used to repeat colors
            setColor(bricks[i][j], colors[i % 7]);
            add(window, bricks[i][j]);
        }

    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Compute default location
    int wCenter = WIDTH / 2;
    int hCenter = HEIGHT / 2;

    GOval circle = newGOval(wCenter, hCenter, 2 * RADIUS, 2 * RADIUS);

    // set ball color
    setFilled(circle, true);
    setColor(circle, "BLACK");

    // Add circle to window
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Align the paddle to bottom-middle of the game's window and
    // elevate the paddle from the bottom by 5 times the paddle height
    int xLocation = (WIDTH - PADDLE_WIDTH) / 2;
    int yLocation = (HEIGHT - PADDLE_HEIGHT * 5) ;
    
    // Instantiate the paddle
    GRect paddle = newGRect(xLocation, yLocation, PADDLE_WIDTH, PADDLE_HEIGHT);

    // set paddle fill color
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

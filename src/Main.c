#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>

/*Prepare textures*/ 
sfSprite* initializeSprite(char* texture);

//variables
/* Set movement flags for both players */
sfBool isPlayer1MovingLeft = sfFalse;
sfBool isPlayer1MovingRight = sfFalse;
sfBool isPlayer2MovingLeft = sfFalse;
sfBool isPlayer2MovingRight = sfFalse;

/* Set movement speed for both players */
float player1MovementSpeed = 300.0f;
float player2MovementSpeed = 300.0f;  

/* Set ball velocity */
sfVector2f ballVelocity = {400.0f, 400.0f};  

/* Set initial positions for both players and ball */
sfVector2f playerOnePosition = {350.0f, 540.0f};
sfVector2f playerTwoPosition = {350.0f, 10.0f};
sfVector2f ballPosition = {350.0f, 250.0f};

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "Ping pong game", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfSprite* playerOne = initializeSprite("./sprites/player.jpg");
    sfSprite* playerTwo = initializeSprite("./sprites/player2.jpg");
    sfSprite* ball = initializeSprite("./sprites/ball.jpg");

    sfSprite_setPosition(playerOne, playerOnePosition);
    sfSprite_setPosition(playerTwo, playerTwoPosition);
    sfSprite_setPosition(ball, ballPosition);

    sfClock* clock = sfClock_create();

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        sfTime deltaTime = sfClock_restart(clock);
        float dt = sfTime_asSeconds(deltaTime);

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
            {
                // Movement
                sfKeyCode keyCode = event.key.code;
                if (keyCode == sfKeyRight)
                {
                    isPlayer1MovingRight = sfTrue;
                }
                else if (keyCode == sfKeyLeft)
                {
                    isPlayer1MovingLeft = sfTrue;
                }
                else if (keyCode == sfKeyD)
                {
                    isPlayer2MovingRight = sfTrue;
                }
                else if (keyCode == sfKeyA)
                {
                    isPlayer2MovingLeft = sfTrue;
                }
            }
            else if (event.type == sfEvtKeyReleased)
            {
                // Handle key release event (still movement)
                sfKeyCode keyCode = event.key.code;
                if (keyCode == sfKeyRight)
                {
                    isPlayer1MovingRight = sfFalse;
                }
                else if (keyCode == sfKeyLeft)
                {
                    isPlayer1MovingLeft = sfFalse;
                }
                else if (keyCode == sfKeyD)
                {
                    isPlayer2MovingRight = sfFalse;
                }
                else if (keyCode == sfKeyA)
                {
                    isPlayer2MovingLeft = sfFalse;
                }
            }
        }

        /* Update player 1 position based on movement flags */
        sfVector2f player1Movement = {0.0f, 0.0f};
        if (isPlayer1MovingRight)
        {
            player1Movement.x += player1MovementSpeed * dt;
        }
        else if (isPlayer1MovingLeft)
        {
            player1Movement.x -= player1MovementSpeed * dt;
        }
        sfVector2f newPlayer1Position = {playerOnePosition.x + player1Movement.x, playerOnePosition.y};
        sfFloatRect player1Bounds = sfSprite_getGlobalBounds(playerOne);
        if (newPlayer1Position.x + player1Bounds.width <= mode.width && newPlayer1Position.x >= 0.0f)
        {
            playerOnePosition = newPlayer1Position;
            sfSprite_setPosition(playerOne, playerOnePosition);
        }

        /* Update player 2 position based on movement flags */
        sfVector2f player2Movement = {0.0f, 0.0f};
        if (isPlayer2MovingRight)
        {
            player2Movement.x += player2MovementSpeed * dt;
        }
        else if (isPlayer2MovingLeft)
        {
            player2Movement.x -= player2MovementSpeed * dt;
        }
        sfVector2f newPlayer2Position = {playerTwoPosition.x + player2Movement.x, playerTwoPosition.y};
        sfFloatRect player2Bounds = sfSprite_getGlobalBounds(playerTwo);
        if (newPlayer2Position.x + player2Bounds.width <= mode.width && newPlayer2Position.x >= 0.0f)
        {
            playerTwoPosition = newPlayer2Position;
            sfSprite_setPosition(playerTwo, playerTwoPosition);
        }

        /* Update ball position */
        sfVector2f ballMovement = {ballVelocity.x * dt, ballVelocity.y * dt};
        sfVector2f newBallPosition = {ballPosition.x + ballMovement.x, ballPosition.y + ballMovement.y};
        sfFloatRect ballBounds = sfSprite_getGlobalBounds(ball);

        /* Check ball collision with player 1 */
        sfFloatRect player1Collision = sfSprite_getGlobalBounds(playerOne);
        if (sfFloatRect_intersects(&player1Collision, &ballBounds, NULL))
        {
            // Reverse ball's vertical velocity
            ballVelocity.y = -ballVelocity.y;

            // Adjust ball's position to prevent sticking to the player
            newBallPosition.y = playerOnePosition.y - ballBounds.height;
        }

        /* Check ball collision with player 2 */
        sfFloatRect player2Collision = sfSprite_getGlobalBounds(playerTwo);
        if (sfFloatRect_intersects(&player2Collision, &ballBounds, NULL))
        {
            // Reverse ball's vertical velocity
            ballVelocity.y = -ballVelocity.y;

            // Adjust ball's position to prevent sticking to the player
            newBallPosition.y = playerTwoPosition.y + player2Bounds.height;
        }

        /* Check ball collision with window edges */
        if (newBallPosition.x + ballBounds.width > mode.width || newBallPosition.x < 0.0f)
        {
            // Reverse ball's horizontal velocity
            ballVelocity.x = -ballVelocity.x;
        }

        if (newBallPosition.y + ballBounds.height > mode.height || newBallPosition.y < 0.0f)
        {
            // Reset ball position to the middle of the window
            newBallPosition.x = mode.width / 2 - ballBounds.width / 2;
            newBallPosition.y = mode.height / 2 - ballBounds.height / 2;
            
            // Reverse ball's vertical velocity
            ballVelocity.y = -ballVelocity.y;
        }

        /* Update ball position */
        ballPosition = newBallPosition;
        sfSprite_setPosition(ball, ballPosition);

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprites */
        sfRenderWindow_drawSprite(window, playerOne, NULL);
        sfRenderWindow_drawSprite(window, playerTwo, NULL);
        sfRenderWindow_drawSprite(window, ball, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRenderWindow_destroy(window);
    sfSprite_destroy(playerOne);
    sfSprite_destroy(playerTwo);
    sfSprite_destroy(ball);
    sfClock_destroy(clock);

    return 0;
}

sfSprite* initializeSprite(char* texture)
{
    sfTexture* spriteTexture = sfTexture_createFromFile(texture, NULL);
    if (!spriteTexture)
        return 1;

    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, spriteTexture, sfTrue);
    return sprite;
}

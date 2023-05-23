#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfTexture* player2Texture;
    sfSprite* player2Sprite;
    sfFont* font;
    sfText* text;
    sfMusic* music;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    /* Load player 1 texture */
    texture = sfTexture_createFromFile("./sprites/player.jpg", NULL);
    if (!texture)
        return 1;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    /* Load player 2 texture */
    player2Texture = sfTexture_createFromFile("./sprites/player2.jpg", NULL);
    if (!player2Texture)
        return 1;
    player2Sprite = sfSprite_create();
    sfSprite_setTexture(player2Sprite, player2Texture, sfTrue);

    /* Set initial positions for both players */
    sfVector2f player1Position = {350.0f, 50.0f};
    sfVector2f player2Position = {350.0f, 500.0f};
    sfSprite_setPosition(sprite, player1Position);
    sfSprite_setPosition(player2Sprite, player2Position);

    /* Set movement flags for both players */
    sfBool isPlayer1MovingLeft = sfFalse;
    sfBool isPlayer1MovingRight = sfFalse;
    sfBool isPlayer2MovingLeft = sfFalse;
    sfBool isPlayer2MovingRight = sfFalse;

    /* Set movement speed for both players */
    float player1MovementSpeed = 0.5f;
    float player2MovementSpeed = 0.5f;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
            {
                // Handle key press event
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
                // Handle key release event
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
            else if (event.type == sfEvtMouseButtonPressed)
            {
                sfMouseButton mouseButton = event.mouseButton.button;
            }
        }

        /* Update player 1 position based on movement flags */
        sfVector2f player1Movement = {0.0f, 0.0f};
        if (isPlayer1MovingRight)
        {
            player1Movement.x += player1MovementSpeed;
        }
        else if (isPlayer1MovingLeft)
        {
            player1Movement.x -= player1MovementSpeed;
        }
        sfVector2f newPlayer1Position = {player1Position.x + player1Movement.x, player1Position.y};
        sfFloatRect player1Bounds = sfSprite_getGlobalBounds(sprite);
        if (newPlayer1Position.x + player1Bounds.width <= mode.width && newPlayer1Position.x >= 0.0f)
        {
            player1Position = newPlayer1Position;
            sfSprite_setPosition(sprite, player1Position);
        }

        /* Update player 2 position based on movement flags */
        sfVector2f player2Movement = {0.0f, 0.0f};
        if (isPlayer2MovingRight)
        {
            player2Movement.x += player2MovementSpeed;
        }
        else if (isPlayer2MovingLeft)
        {
            player2Movement.x -= player2MovementSpeed;
        }
        sfVector2f newPlayer2Position = {player2Position.x + player2Movement.x, player2Position.y};
        sfFloatRect player2Bounds = sfSprite_getGlobalBounds(player2Sprite);
        if (newPlayer2Position.x + player2Bounds.width <= mode.width && newPlayer2Position.x >= 0.0f)
        {
            player2Position = newPlayer2Position;
            sfSprite_setPosition(player2Sprite, player2Position);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprites */
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_drawSprite(window, player2Sprite, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfSprite_destroy(player2Sprite);
    sfTexture_destroy(player2Texture);
    sfRenderWindow_destroy(window);
    return 0;
}

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfFont* font;
    sfText* text;
    sfMusic* music;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    /* Load a sprite to display */
    texture = sfTexture_createFromFile("./sprites/player.jpg", NULL);
    if (!texture)
        return 1;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

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
                    sfVector2f currentPosition = sfSprite_getPosition(sprite);
                    sfVector2f moveRight = {10.0f, 0.0f};
                    sfVector2f newPosition = {currentPosition.x + moveRight.x, currentPosition.y + moveRight.y};

                    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(sprite);
                    if (newPosition.x + spriteBounds.width <= mode.width)
                    {
                        sfSprite_setPosition(sprite, newPosition);
                    }
                }
                else if (keyCode == sfKeyLeft)
                {
                    sfVector2f currentPosition = sfSprite_getPosition(sprite);
                    sfVector2f moveLeft = {-10.0f, 0.0f};
                    sfVector2f newPosition = {currentPosition.x + moveLeft.x, currentPosition.y + moveLeft.y};

                    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(sprite);
                    if (newPosition.x >= 0.0f)
                    {
                        sfSprite_setPosition(sprite, newPosition);
                    }
                }
            }
            else if (event.type == sfEvtMouseButtonPressed)
            {
                sfMouseButton mouseButton = event.mouseButton.button;
            }
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return 0;
}

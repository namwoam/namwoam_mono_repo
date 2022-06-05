import pygame as pg

pg.init()

width, height = 640, 480
screen = pg.display.set_mode((width, height))
bg = pg.Surface(screen.get_size())
bg = bg.convert()
bg.fill((255, 255, 255))

screen.blit(bg, (0, 0))

image = pg.image.load('frog.jpg')
print(image)
image.convert()
bg.blit(image, (0, 0))
screen.blit(bg, (0, 0))
pg.display.update()

running = True
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
pg.quit()

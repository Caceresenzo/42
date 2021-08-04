<template>
  <v-main class="fill-height">
    <v-row class="fill-height">
      <v-col cols="2" align="center" class="vertical">
        <game-score
          v-if="leftPlayer"
          :player="leftPlayer"
          :max="maxRound"
          status
        />
      </v-col>
      <v-col cols="8">
        <canvas
          id="myCanvas"
          :width="width"
          :height="height"
          tabindex="0"
          @keydown="onKeyDown"
          @keyup="onKeyUp"
          @blur="refocus"
          style="position: absolute"
        ></canvas>
      </v-col>
      <v-col cols="2" align="center" class="vertical">
        <game-score
          v-if="rightPlayer"
          :player="rightPlayer"
          :max="maxRound"
          status
        />
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator' // propre a nuxt
import { Socket } from 'vue-socket.io-extended'
import { Match, User } from '~/models'
import { Game, Player, Rectangle, Settings, Side } from '~/models/Game'

enum State {
  WAITING,
  PLAYING,
}

class VisibleObject {
  constructor(
    public x: number,
    public y: number,
    public width: number,
    public height: number
  ) {}

  copyPosition({ x, y }: { x: number; y: number }) {
    this.x = x
    this.y = y
  }

  updatePosition(x: number, y: number) {
    this.x = x
    this.y = y
  }

  draw(ctx: CanvasRenderingContext2D) {
    /* empty */
  }
}

class Paddle extends VisibleObject {
  public shadow = false

  constructor(x: number, y: number) {
    super(x, y, 20, 100)
  }

  draw(ctx: CanvasRenderingContext2D) {
    ctx.fillStyle = this.color
    ctx.fillRect(this.x, this.y, 20, 100)
  }

  get color() {
    if (this.shadow) {
      return 'lightgray'
    }

    return 'white'
  }
}

class Ball extends VisibleObject {
  constructor(x: number, y: number) {
    super(x, y, 15, 15)
  }

  draw(ctx: CanvasRenderingContext2D) {
    ctx.beginPath()
    ctx.arc(this.x, this.y, this.width, 0, Math.PI * 2)
    ctx.fillStyle = 'white'
    ctx.fill()
    ctx.closePath()
  }
}

@Component
export default class Page extends Vue {
  destroyed = true
  canvas: HTMLCanvasElement | null = null
  ctx: CanvasRenderingContext2D | null = null

  private loopInterval: NodeJS.Timeout | null = null

  height: number = 600
  width: number = 800

  ball = new Ball(300, 200)

  paddle = {
    [Side.LEFT]: new Paddle(15, 10),
    [Side.RIGHT]: new Paddle(770, 10),
  }

  myPaddle: Paddle | null = null

  player = {
    [Side.LEFT]: null as unknown as Player,
    [Side.RIGHT]: null as unknown as Player,
  }

  side: Side = Side.LEFT
  obstacles: Array<Rectangle> = []
  settings: Settings | null = null

  message: string = ''
  countdown: number = 3
  state = State.WAITING

  keys = {
    up: false,
    down: false,
  }

  get id() {
    return this.$route.params.id
  }

  onKeyDown(event: KeyboardEvent) {
    if (!this.inputEnabled) {
      return
    }

    switch (event.key) {
      case 'ArrowDown': {
        this.keys.down = true
        break
      }

      case 'ArrowUp': {
        this.keys.up = true
        break
      }
    }
  }

  onKeyUp(event: KeyboardEvent) {
    if (!this.inputEnabled) {
      return
    }

    switch (event.key) {
      case 'ArrowDown': {
        this.keys.down = false
        break
      }

      case 'ArrowUp': {
        this.keys.up = false
        break
      }
    }
  }

  refocus() {
    this.$nextTick(() => {
      if (!this.destroyed) {
        this.canvas?.focus()
      }
    })
  }

  updatePaddles() {
    if (
      this.player[Side.LEFT].user.id === this.$store.state.auth.user.id ||
      this.player[Side.RIGHT].user.id === this.$store.state.auth.user.id
    ) {
      const paddle = this.myPaddle

      if (!paddle) {
        return
      }

      let newY = paddle.y
      const prevY = newY

      if (this.keys.up && !this.keys.down) {
        newY -= 4 * (this.settings?.paddleVelocity || 1)
      } else if (this.keys.down && !this.keys.up) {
        newY += 4 * (this.settings?.paddleVelocity || 1)
      }

      if (newY <= 0) {
        newY = 10
      } else {
        const bottom = this.height - paddle.height

        if (newY >= bottom) {
          newY = bottom - 10
        }
      }

      if (newY !== prevY) {
        paddle.y = newY

        this.$socket.client.emit(
          'game_move',
          {
            gameId: this.id,
            y: newY,
          },
          (err: any) => {
            if (err) {
              paddle.y = prevY
            }
          }
        )
      }
    }
  }

  loop(): void {
    if (!this.ctx) {
      return
    }

    this.ctx.fillStyle = `${this.$vuetify.theme.themes.dark.primary}`
    this.ctx.fillRect(0, 0, this.width, this.height)

    this.ctx.strokeStyle = 'grey'
    this.ctx.moveTo(400, 20)
    this.ctx.lineTo(400, 580)
    this.ctx.stroke()

    for (const obstacle of this.obstacles) {
      this.ctx.fillStyle = 'white'
      this.ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height)
    }

    this.ball.draw(this.ctx)
    if (this.state === State.PLAYING) {
      this.updatePaddles()
    }

    this.paddle[Side.LEFT].draw(this.ctx)
    this.paddle[Side.RIGHT].draw(this.ctx)

    if (this.myPaddle) {
      this.myPaddle.draw(this.ctx)
    }

    if (this.state === State.WAITING) {
      if (this.countdown !== -1) {
        this.ctx.save()
        const x = this.width / 2
        const y = this.height / 8

        this.ctx.font = '80px Nunito'
        this.ctx.textAlign = 'center'
        this.ctx.strokeStyle = 'black'
        this.ctx.lineWidth = 4
        this.ctx.strokeText(`${this.countdown}`, x, y)
        this.ctx.fillStyle = 'white'
        this.ctx.fillText(`${this.countdown}`, x, y)
        this.ctx.restore()
      }

      if (this.message) {
        this.ctx.save()
        const x = this.width / 2
        const y = (this.height / 8) * 7

        this.ctx.font = '40px Nunito'
        this.ctx.textAlign = 'center'
        this.ctx.strokeStyle = 'black'
        this.ctx.lineWidth = 4
        this.ctx.strokeText(this.message, x, y)
        this.ctx.fillStyle = 'white'
        this.ctx.fillText(this.message, x, y)
        this.ctx.restore()
      }
    }
  }

  @Socket('game_state')
  onGameState(data: Game) {
    const { paddle, player, ball, countdown } = data

    this.ball.copyPosition(ball)

    this.player = player

    this.paddle[Side.LEFT].y = paddle[Side.LEFT].y
    this.paddle[Side.RIGHT].y = paddle[Side.RIGHT].y

    if (!this.myPaddle) {
      this.initializeMyPaddle()
    }

    this.countdown = countdown

    if (countdown !== -1) {
      this.state = State.WAITING
    } else if (this.state !== State.PLAYING) {
      this.state = State.PLAYING
      this.message = ''
    }
  }

  @Socket('game_scored')
  onGameScored(data: Game) {
    const { scorer } = data

    this.message = `${scorer!.user.username} scored!`
  }

  @Socket('game_end')
  onGameEnd(match: Match) {
    const { id } = match

    if (id === undefined) {
      this.$dialog.notify.error(`No match returned`)
      this.$router.replace({
        path: '/',
      })
    } else {
      this.$router.replace({
        path: `/matches/${id}`,
      })
    }
  }

  @Socket('game_exit')
  async onGameExit(data: Game) {
    await this.$dialog.info({
      text: 'game exit',
    })

    this.$router.push({
      path: `/`,
    })
  }

  mounted() {
    this.destroyed = false
    this.refocus()

    this.canvas = document.getElementById('myCanvas') as HTMLCanvasElement
    this.ctx = this.canvas.getContext('2d') as CanvasRenderingContext2D
    this.ctx.fillStyle = `${this.$vuetify.theme.themes.dark.primary}`
    this.ctx.fillRect(0, 0, this.width, this.height)

    this.$socket.client.emit(
      'game_connect',
      {
        gameId: this.id,
      },
      (error: any, body: Game) => {
        if (this.destroyed) {
          return
        }

        if (error) {
          this.$router.push({
            path: `/`,
          })

          this.$dialog.notify.error(`Could not connect to game: ${error}`)
          return
        }
        const {
          player,
          ball,
          paddle,
          countdown,
          map: { obstacles },
          settings,
        } = body

        if (player[Side.LEFT].user.id === this.$store.state.auth.user.id) {
          this.side = Side.LEFT
        } else {
          this.side = Side.RIGHT
        }

        this.player = player

        this.ball.copyPosition(ball)
        this.paddle[Side.LEFT].copyPosition(paddle[Side.LEFT])
        this.paddle[Side.RIGHT].copyPosition(paddle[Side.RIGHT])

        this.initializeMyPaddle()

        this.countdown = countdown
        this.obstacles = obstacles
        this.settings = settings

        this.loopInterval = setInterval(() => this.loop(), 1000 / 60)
      }
    )
  }

  initializeMyPaddle() {
    const reference = this.paddle[this.side]
    reference.shadow = true

    this.myPaddle = new Paddle(reference.x, reference.y)
  }

  beforeDestroy() {
    this.destroyed = true
    this.$socket.client.emit('game_disconnect')

    if (this.loopInterval) {
      clearInterval(this.loopInterval)
      this.loopInterval = null
    }
  }

  get otherSide(): Side {
    return this.side === Side.LEFT ? Side.RIGHT : Side.LEFT
  }

  get inputEnabled(): boolean {
    return this.state === State.PLAYING
  }

  get leftPlayer(): Player {
    return this.player[Side.LEFT]
  }

  get rightPlayer(): Player {
    return this.player[Side.RIGHT]
  }

  get maxRound() {
    return this.settings?.pointToWin
  }
}
</script>

<style>
  #myCanvas {
    position: absolute;
    padding: 0;
    margin: auto;
    display: block;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    width: 50%;
    border: 1px solid black;
  }

  .vertical {
    display: flex;
    align-items: center;
    justify-content: center;
  }
</style>

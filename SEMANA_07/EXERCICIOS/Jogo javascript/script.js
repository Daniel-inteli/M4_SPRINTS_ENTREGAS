    let url = "http://IP-DO-SEU-ESP32";

    // interactives
    var btIniciar;
    var player1;
    var player2;
    var ball;
    var painelPoints1;
    var painelPoints2;
    var painelWinner;
    //animations
    var game,frames;

    //positions
    var posBallX,posBallY;
    var posPl1X,posPl1Y;
    var posPl2X,posPl2Y;

    //directions
    var dirPY1,dirPY2;

    //inicial position
    var posPl1InitX=0, posPl1InitY=240,posPl2InitX=1210, posPl2InitY=240,posBallIniX=620,posBallIniY=325;
    
    //Sizes
    var campoX=0,campoY=0,screenW=1280,screenH=735;
    var barraW=30,barraH=200,ballW=30,ballH=30;

    //
    var ballX,ballY;

    //speed
    var ballSpeed,pl1Speed,pl2Speed;

    //control
    var score1=0;
    var score2=0
    var button;
    game=false;
   
    
    function plControl(){
      if(game){
        posPl1Y+=pl1Speed*dirPY1;
        if(
          ((posPl1Y+barraH) >=screenH)||((posPl1Y)<=5)
          ){
          posPl1Y+=(pl1Speed*dirPY1)*(-1);
        }
        player1.style.top=posPl1Y + "px";
        posPl2Y+=pl2Speed*dirPY2;
        if(
          ((posPl2Y+barraH) >=screenH)||((posPl2Y)<=5)
          ){
          posPl2Y+=(pl2Speed*dirPY2)*(-1);
        }
        player2.style.top=posPl2Y + "px";
       }
    }
    function ballControl(){
      posBallX+=ballSpeed*ballX;
      posBallY+=ballSpeed*ballY;
      //colisao
      if(
        (posBallX <= posPl1X+barraW) && 
        ((posBallY+ballH >= posPl1Y) && (posBallY <= posPl1Y+barraH))
      ){
        ballY=(((posBallY+(ballH/2)) - (posPl1Y+(barraH/2)))/32);
        ballX*=-1;

      }
      if(
        (posBallX >= posPl2X+barraW) && 
        ((posBallY+ballH >= posPl2Y) && (posBallY <= posPl2Y+barraH))
      ){
        ballY=(((posBallY+(ballH/2)) - (posPl2Y+(barraH/2)))/32);
        ballX*=-1;
      }
      //limite superior e inferior
      if((posBallY >=700) || (posBallY<=10)){
        ballY*=-1;
      }
      //limite de tela eixo x
      if(
        posBallX>=(screenW-ballW)){
          ballSpeed=0;
          posBallX=posBallIniX;
          posBallY=posBallIniY +(ballH);
          posPl1Y=posPl1InitY;
          posPl2Y=posPl2InitY;
          player1.style.top=posPl1Y + "px";
          player2.style.top=posPl2Y + "px";
          score1++;
          painelPoints1.value=score1;
          game=false;
        }
        else if(
          posBallX<=5){
          ballSpeed=0;
          posBallX=posBallIniX;
          posBallY=posBallIniY
          posPl1Y=posPl1InitY;
          posPl2Y=posPl2InitY;
          player1.style.top=posPl1Y + "px";
          player2.style.top=posPl2Y + "px";
          score2++;
          painelPoints2.value=score2;
          game=false;
          }
      
      ball.style.top=posBallY + "px";
      ball.style.left=posBallX +"px";
    }
    function vencedor(){
      if(painelPoints1.value==3){
        score1=0;
        score2=0;
        painelPoints1.value=0;
        painelPoints2.value=0;
        ganhador_x();
        game=false;
        
      }else if (painelPoints2.value==3){
        score1=0;
        score2=0;
        painelPoints1.value=0;
        painelPoints2.value=0;
        ganhador_0();
        game=false;
        
      }
    }
    function teclaDw(){
      button=event.keyCode;
      if(button==87){//tecla pra cima
         dirPY1=-1;
      }else if(button==83){
         dirPY1=+1;
      }
      else if(button==38){
         dirPY2=-1;
      }else if(button==40){
         dirPY2=+1;
      }
    }
    function teclaUp(){
      button=event.keyCode;
      if(button==87){
         dirPY1=0;
      }else if(button==83){
         dirPY1=0;
      }else if(button==38){
         dirPY2=0;
      }else if(button==40){
         dirPY2=0;
      }
    }
    function pong(){
      if(game){
        plControl();
        ballControl();
        vencedor();
      }
      frames=requestAnimationFrame(pong)
    }
    function startGame(){
      if(!game){
         ballSpeed=pl1Speed=pl2Speed=6;
         cancelAnimationFrame(frames);
         game=true;
         dirPY1=0;
         dirPY2=0;
         ballY=0;
         if((Math.random()*10)<5){
          ballX=-1;
        }else{
          ballX=+1;
        }
         posBallX=posBallIniX;
         posBallY=posBallIniY;
         posPl1Y=posPl1InitY;
         posPl1X=posPl1InitX;
         posPl2X=posPl2InitX;
         posPl2Y=posPl2InitY;
         painelWinner.value="";
         pong();
      }

    }
    function start(){
      btIniciar=document.getElementById("btIniciar");
      btIniciar.addEventListener("click",startGame);
      player1=document.getElementById("dvJogador1");
      player2=document.getElementById("dvJogador2");
      ball=document.getElementById("dvBola");
      painelPoints1=document.getElementById("txtPontos1");
      painelPoints2=document.getElementById("txtPontos2");
      painelWinner=document.getElementById("txtVencedor");
      document.addEventListener("keydown",teclaDw);
      document.addEventListener("keyup",teclaUp);
    }
    window.addEventListener("load",start);
    function ganhador_x(){
      painelWinner.value="jogador1 venceu!";
      $.ajax({
        url: url + "jogador1",
      })
    }

    function ganhador_0(){
      painelWinner.value="jogador2 venceu!";
      $.ajax({
      url: url + "jogador2",
    })
    }

package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URL;

public class Main {

    static int[] displaybuffer = new int[128*4];
    static int[] megabuffer= new int[128*32];

    static int[] sprite = new int[]{
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
            0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
            0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,
            0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,
            0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,
            0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,
            0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,
            0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
            0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,
            0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

    static void buffer_make(int x, int y){

        int width = 16;
        int height = 16;

        int sy;
        int sx;
        for(sy = 0; sy < height; sy++ ){
            for(sx = 0; sx < width; sx++){
                megabuffer[(sy+y)*128 + x+sx] = sprite[sy*width + sx];
            }
        }
    }

    static void toscreenbuffer(){
        int index = 0;
        int y;
        int x;
        int j;
        for (y = 0; y < 4; y++) {
            for(x = 0; x < 128; x++) {
                int sum = 0;
                for(j = 0; j < 8; j++) {
                    sum += megabuffer[((y*8) + j)*128 + x] * Math.pow(2, j);
                }
                displaybuffer[index] = sum;
                index++;
            }
        }
        for(int i = 0; i < 128*4; i++) {
            System.out.print(displaybuffer[i]+",");
            if(i > 1 && i % 32 == 0)
                System.out.print("\n");
        }
    }

    public static void main(String[] args) {
        //debug for buffer c class
        //buffer_make(0,0);
        //toscreenbuffer();

        //args = new String[]{"image1.png"};

        if (args.length == 0 ) {
           System.out.println("no image file was given add a filename as argument");
           System.exit(-1);
        }

        if (args[0].equals("")) {
            System.out.println("no image file was given add a filename as argument");
            System.exit(-1);
        }


        File imageFile = new File(args[0]);

        String str  = "";
        BufferedImage image = null;
        try {
            image = ImageIO.read(imageFile);
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("" + image.getWidth()+ "," + image.getHeight()+",");
        for(int y = 0; y < image.getHeight(); y++){
            for(int x = 0; x < image.getWidth(); x++) {
            int pixel = image.getRGB(x,y) == -1 ? 0 : 1;

            System.out.print(""+pixel+",");
                if(x == image.getWidth()-1)
                    System.out.print("\n");
            }
    }

    /*
        for (int y = 0; y < image.getHeight()/8; y++) {
            for(int x = 0; x < image.getWidth(); x++) {
                int sum = 0;
                for(int j = 0; j < 8; j++) {
                    int pixel = (image.getRGB(x,y*8+j) == -1 ? 0 : 1);
                    sum +=  pixel * Math.pow(2, j);
                }
                System.out.print(sum+",");
            }
        }

        for (int i = 0; i < 32*128; i++){
            if((i % 48) == 0)
                System.out.print("\n");
            System.out.print("0,");
        }
  */

    }
}



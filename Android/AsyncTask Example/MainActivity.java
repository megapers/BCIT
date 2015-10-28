package com.example.timur.lab6;

import android.graphics.Color;
import android.graphics.Paint;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void changeColor(View view)
    {
        Random rand;
        RelativeLayout layout;
        int color;

        rand = new Random();
        layout = (RelativeLayout)findViewById(R.id.layout);
        color = Color.argb(255, rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
        layout.setBackgroundColor(color);
    }

    public void countDown(View view)
    {
        TestTask task = new TestTask();
        task.execute();
    }


    private class TestTask extends AsyncTask<Void, Void, Void> {

        int seconds = 5;
        TextView lable;
        Button changeColor = (Button)findViewById(R.id.button);

        @Override
        protected void onPreExecute() { //grab lable
            lable = (TextView)findViewById(R.id.textView);
            changeColor.setEnabled(false);
        }

        @Override
        protected Void doInBackground(Void ... x) {//decrement counter
            try {
                for(seconds = 5; seconds>=1; seconds--)
                    {
                    Thread.sleep(1000);
                    runOnUiThread(new Runnable() {//OnProgressUpdate - can substitute runOnUiThread - check
                        @Override
                        public void run()
                        {
                            lable.setText(seconds + "");
                        }
                    });

                     }
            }catch (Exception e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {//reenabe button on
            changeColor.setEnabled(true);
        }
    }



}

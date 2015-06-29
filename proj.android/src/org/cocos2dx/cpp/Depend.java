package org.cocos2dx.cpp;

import android.os.Environment;

import java.io.File;

/**
 * Created by ff on 15-3-11.
 */
public class Depend {
    public static String getResSdPath(){
        File sdCard = Environment.getExternalStorageDirectory();
        if (!sdCard.exists()) {
            return null;
        }

        File dir = new File(sdCard.getAbsolutePath() + "/com.ynnet.soul");
        if (!dir.exists()) {
            boolean done = dir.mkdir();
            System.out.println(done);
        }

        return dir.getAbsolutePath();
    }
}

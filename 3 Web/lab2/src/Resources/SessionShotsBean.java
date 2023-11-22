package Resources;

import java.io.Serializable;
import java.util.LinkedList;

public class SessionShotsBean implements Serializable {

    private static final long serialVersionUID = 2041275512219239990L;

    public LinkedList<String> getShots() {
        return shots;
    }

    public void setShots(LinkedList<String> shots) {
        this.shots = shots;
    }

    private LinkedList<String> shots;

    public SessionShotsBean() {
        shots = new LinkedList<String>();
    }

    public SessionShotsBean(LinkedList<String> shotsIn) {
        shots = shotsIn;
    }

    public void addFirst(String shot) {
        shots.addFirst(shot);
    }

    public String writeAll() {
        StringBuilder strBuild = new StringBuilder();

        shots.stream().map(str -> {
            String[] shot = str.split(" ");
            String trS = "<tr>";
            String trE = "</tr>";
            String tdS = "<td>";
            String tdE = "</td>";
            return (trS +
                    tdS + shot[0] + tdE +
                    tdS + shot[1] + tdE +
                    tdS + shot[2] + tdE +
                    tdS + shot[3] + tdE +
                    tdS + shot[4] + tdE +
                    tdS + shot[5] + tdE +
                    trE
            );
        }).forEachOrdered(str -> strBuild.append(str));

        return strBuild.toString();
    }

    public String printAll() {
        StringBuilder strBuild = new StringBuilder();

        shots.stream().map(str -> {
            String[] shot = str.split(" ");
            double x = Double.parseDouble(shot[0]);
            double y = Double.parseDouble(shot[1]);
            double r = Double.parseDouble(shot[2]);

            return (
                    "<circle cx=\"" + (150 + 120 * (x / r)) + "\" cy=\"" + (150 - 120 * (y / r)) + "\" r=\"5\" fill=\"rgb(255,0,255)\" stroke-width=\"1\"\n stroke=\"rgb(0,0,0)\"/>"
            );
        }).forEachOrdered(str -> strBuild.append(str));

        return strBuild.toString();
    }

}

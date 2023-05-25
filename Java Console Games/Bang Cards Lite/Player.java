import java.util.ArrayList;
import java.util.Objects;

public class Player {
    private final String name;
    private final ArrayList<Card> handCards;
    private final ArrayList<Card> tableCards;

    private boolean alive;
    int lives;

    Player(String name) {
        this.name = name;
        this.lives = 4;
        handCards = new ArrayList<Card>();
        tableCards = new ArrayList<Card>();
        alive = true;
    }

    public String getName() {
        return name;
    }

    public boolean isAlive() {
        return alive;
    }

    public int getLives() {
        return lives;
    }

    public int getNumberOfCardsInHand() {
        return handCards.size();
    }
    public int getNumberOfCardsOnTable() {
        return tableCards.size();
    }
    public void addCardToHand(Card card) {
        handCards.add(card);
    }
    public void addCardToTable(Card card) {
        tableCards.add(card);
    }

    public void printHandCards() {
        int i;
        System.out.print("Player: " + this.name + " has following cards in Hand:\n");
        for(i=0; i<handCards.size(); i++) {
            System.out.print("\t" + (i+1) + ". " + handCards.get(i).getName() + "\n");
        }
    }

    public void printTableCards() {
        int i;
        System.out.print("Player: " + this.name + " has following cards on table:\n");
        for(i=0; i<tableCards.size(); i++) {
            System.out.print("\t" + (i+1) + ". " + tableCards.get(i).getName() + "\n");
        }
    }

    public Card drawCardFromHand(int index) {

        Card c = handCards.get(index);
        handCards.remove(index);
        return c;
    }

    public Card drawCardFromTableIndex(int index) {
        Card c = tableCards.get(index);
        tableCards.remove(index);
        return c;
    }

    public void drawCardFromTable(String cardName) {
        if(tableCards.isEmpty())
            return;
        int index;
        for(index = 0; index < tableCards.size(); index++) {
            if(Objects.equals(tableCards.get(index).getName(), cardName)) {
                break;
            }
        }
        Card c = tableCards.get(index);
        tableCards.remove(index);
    }

    public Card getSpecificCard(String cardName) {
        for(int i=0; i<handCards.size(); i++) {
            if(Objects.equals(handCards.get(i).getName(), cardName) && !Objects.equals(handCards.get(i).getName(), "Prison Card") && !Objects.equals(handCards.get(i).getName(), "Barrel Card") && !Objects.equals(handCards.get(i).getName(), "Dynamite Card")) {
                Card c = handCards.get(i);
                handCards.remove(i);
                return c;
            }
        }

        for (Card tableCard : tableCards) {
            if (Objects.equals(tableCard.getName(), cardName)) {
                return tableCard;
            }
        }

        return null;
    }

    public void reduceLive() {
        lives--;
    }

    public void addLive() {
        lives++;
    }

    public void makeDead() {
        alive = false;
    }
}

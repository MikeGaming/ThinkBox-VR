using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.UIElements;

public class SymbolAnswer : MonoBehaviour
{
    int[] symbolOrder = new int[4] { 5, 5, 5, 5 };
    List<int> symbolNumbers = Enumerable.Range(1, 4).ToList();
    List<int> symbolOrderNumbers = Enumerable.Range(1, 4).ToList();
    [SerializeField] MessageListener messageListener;
    [SerializeField] Text[] symbolAnswerTexts = new Text[4];
    bool triggered;
    int r;

    void Start()
    {
        for(int i = 0; i < symbolOrder.Length; i++)
        {
            r = symbolNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolOrder[i] = r;
            if (r == 1)
            {
                symbolAnswerTexts[i].text = "▲";
            }
            else if (r == 2)
            {
                symbolAnswerTexts[i].text = "●";
            }
            else if (r == 3)
            {
                symbolAnswerTexts[i].text = "■";
            }
            else if (r == 4)
            {
                symbolAnswerTexts[i].text = "◆";
            }
            symbolNumbers.Remove(r);
            print(r);
        }
        messageListener.SendTextData("#" + symbolOrder[0] + symbolOrder[1] + symbolOrder[2] + symbolOrder[3]);
    }
    void Update()
    {
        if (messageListener.lastMessage == "s" && !triggered && symbolOrderNumbers.Count != 0)
        {
            triggered = true;
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
        }
        else if(messageListener.lastMessage != "s")
        {
            triggered = false;
        }
    }
}

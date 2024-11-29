using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class SymbolAnswer : MonoBehaviour
{
    int[] symbolOrder = new int[4] { 5, 5, 5, 5 };
    List<int> symbolNumbers = Enumerable.Range(1, 4).ToList();
    List<int> symbolOrderNumbers = Enumerable.Range(1, 4).ToList();
    [SerializeField] MessageController messageListener;
    [HideInInspector] public string lastMessage_symbol;
    [SerializeField] Text[] symbolAnswerTexts = new Text[4];
    bool triggered;
    int r;

    void Start()
    {
        for (int i = 0; i < symbolOrder.Length; i++)
        {
            r = symbolNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolOrder[i] = r;
            if (r == 1)
            {
                symbolAnswerTexts[i].text = "◆";
            }
            else if (r == 2)
            {
                symbolAnswerTexts[i].text = "■";
            }
            else if (r == 3)
            {
                symbolAnswerTexts[i].text = "●";
            }
            else if (r == 4)
            {
                symbolAnswerTexts[i].text = "▲";
            }
            symbolNumbers.Remove(r);
            print(r);
        }
        StartCoroutine(SendText("#" + symbolOrder[0] + symbolOrder[1] + symbolOrder[2] + symbolOrder[3]));
    }
    IEnumerator SendText(string text)
    {
        yield return new WaitForSeconds(1f);
        messageListener.SendTextData(text);
        StopAllCoroutines();
    }
    void Update()
    {
        if (lastMessage_symbol == "s" && !triggered && symbolOrderNumbers.Count != 0)
        {
            triggered = true;
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
        }
        else if (lastMessage_symbol != "s")
        {
            triggered = false;
        }
    }
}

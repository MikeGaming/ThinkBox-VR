using UnityEngine;

public class EyeSelectionManager : MonoBehaviour
{
    [SerializeField] private SelectionEye leftEye;
    [SerializeField] private SelectionEye rightEye;

    private float selectionTimer = 0f;
    private GameObject previousSelection;
    private GameObject currentCandidate;
    private const float selectionDuration = 1f;

    private void Update()
    {
        GameObject newCandidate = null;

        bool bothEyesSelectingSame =
            leftEye.selecting &&
            rightEye.selecting &&
            leftEye.selectedObject != null &&
            rightEye.selectedObject != null &&
            leftEye.selectedObject == rightEye.selectedObject;

        if (bothEyesSelectingSame)
        {
            newCandidate = leftEye.selectedObject.gameObject;
            Debug.Log($"Both eyes are selecting: {leftEye.selectedObject.name}");
        }

        // Remove highlight from previous candidate if changed
        if (currentCandidate != newCandidate)
        {
            if (currentCandidate != null)
            {
                var prevSelectable = currentCandidate.GetComponent<SelectableObject>();
                prevSelectable?.SetHighlightActive(false);
            }
            selectionTimer = 0f;
            currentCandidate = newCandidate;
        }

        if (currentCandidate != null)
        {
            var selectable = currentCandidate.GetComponent<SelectableObject>();
            if (selectable != null && !selectable.IsSelected())
            {
                selectable.SetHighlightActive(true);
                selectionTimer += Time.deltaTime;
                if (selectionTimer >= selectionDuration)
                {
                    Debug.Log($"Object selected for {selectionDuration} seconds: {currentCandidate.name}");
                    selectable.Select();
                    selectionTimer = 0f;
                }
            }
        }
        else
        {
            if (leftEye.selecting && leftEye.selectedObject != null)
            {
                Debug.Log($"Left eye selects: {leftEye.selectedObject.name}");
            }
            else if (rightEye.selecting && rightEye.selectedObject != null)
            {
                Debug.Log($"Right eye selects: {rightEye.selectedObject.name}");
            }
            else
            {
                Debug.Log("No selection from either eye.");
            }
        }

        // Handle deselection if selection changed
        if (previousSelection != null && previousSelection != currentCandidate)
        {
            var prevSelectable = previousSelection.GetComponent<SelectableObject>();
            if (prevSelectable != null && prevSelectable.IsSelected())
            {
                prevSelectable.Deselect();
                Debug.Log($"Deselected previous object: {previousSelection.name}");
            }
            else if (prevSelectable != null)
            {
                prevSelectable.SetHighlightActive(false);
            }
        }

        previousSelection = currentCandidate;
    }
}
